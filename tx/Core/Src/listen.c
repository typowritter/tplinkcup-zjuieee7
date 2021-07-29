#include <stdbool.h>
#include <math.h>
#include "listen.h"
#include "window.h"

#define SAMPLING_RATE       292683   /* ADC 采样率 */
#define ADC_BUFLEN          1024     /* 约 3ms */
#define IDLE_BUFLEN         (ADC_BUFLEN/8)  /* 约 0.4ms */

/* 待调整参数 */
#define THRESH_FREQ_D   1000000     /* 导频信号goertzel能量阈值 */
#define THRESH_SIGNAL   3000000000  /* 传输信号goertzel能量阈值 */

static uint16_t adc_buffer[ADC_BUFLEN];

static const uint16_t freq_points[4] =
{
  FREQ_1, FREQ_2, FREQ_3, FREQ_4
};

static double goertzel_power(int num, uint16_t freq, const uint16_t *data);

void wait_for_signal()
{
  double power;
  while (1)
  {
    HAL_ADC_Start_DMA(&adc_dev, (uint32_t *)adc_buffer, IDLE_BUFLEN);
    while (HAL_DMA_GetState(&adc_dma_dev) == HAL_DMA_STATE_BUSY);

    power = goertzel_power(IDLE_BUFLEN, FREQ_D, adc_buffer);
    if (power < THRESH_FREQ_D)
      return;
  }
}

uint8_t decode_signal()
{
  uint8_t res = 0;
  double pwr;

  /* 低4位 */
  HAL_ADC_Start_DMA(&adc_dev, (uint32_t *)adc_buffer, ADC_BUFLEN);
  while (HAL_DMA_GetState(&adc_dma_dev) == HAL_DMA_STATE_BUSY);

  for (int freq_ix = 0; freq_ix < 4; ++freq_ix)
  {
    pwr = goertzel_power(ADC_BUFLEN, freq_points[freq_ix], adc_buffer);
    if (is_significent(pwr))
      res |= (1<<freq_ix);
  }

  wait_for_signal();

  /* 高4位 */
  HAL_ADC_Start_DMA(&adc_dev, (uint32_t *)adc_buffer, ADC_BUFLEN);
  while (HAL_DMA_GetState(&adc_dma_dev) == HAL_DMA_STATE_BUSY);

  for (int freq_ix = 4; freq_ix < 8; ++freq_ix)
  {
    pwr = goertzel_power(ADC_BUFLEN, freq_points[freq_ix-4], adc_buffer);
    if (pwr > THRESH_SIGNAL)
      res |= (1<<freq_ix);
  }

  return res;
}

static double goertzel_power(int num, uint16_t freq, const uint16_t *data)
{
  double omega, cosine, coeff, q0, q1, q2;

  int k = (int) (0.5 + ((num * freq) / (double)SAMPLING_RATE));
  omega = (2.0 * M_PI * k) / num;
  cosine = cos(omega);
  coeff = 2.0 * cosine;
  q1 = 0;
  q2 = 0;
  for (int i = 0; i < num; i++)
  {
    q0 = coeff * q1 - q2 + (double)data[i]*hanning_1024[i];
    q2 = q1;
    q1 = q0;
  }
  return q1*q1 + q2*q2 - coeff*q1*q2;
}
