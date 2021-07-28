#include <string.h>
#include <stdbool.h>
#include "wavegen.h"
#include "sin_lut.h"
#include "stm32f1xx_hal_dac.h"
#include "tim.h"
#include "delay.h"

#define FREQ_POINTS         4  /* 同时处理4个频点 */
#define PERIODS_PER_CYCLE   4  /* 使频率最低的分量有完整的4个周期 */

#define FREQ_1  4000
#define FREQ_2  8000
#define FREQ_3  12000
#define FREQ_4  19000
#define FREQ_D  30000

#define FTW_D   (FREQ_D * PHASE_ACC_MAX / DDS_SAMPLE_FREQ)

#define OUTPUT_BUFLEN   (DDS_SAMPLE_FREQ / FREQ_1 * PERIODS_PER_CYCLE)

static const lut_index_t ftw[FREQ_POINTS] =
{
  FREQ_1 * PHASE_ACC_MAX / DDS_SAMPLE_FREQ,
  FREQ_2 * PHASE_ACC_MAX / DDS_SAMPLE_FREQ,
  FREQ_3 * PHASE_ACC_MAX / DDS_SAMPLE_FREQ,
  FREQ_4 * PHASE_ACC_MAX / DDS_SAMPLE_FREQ,
};

static dac_data_t dac_buf[OUTPUT_BUFLEN];

/**
 * 准备波形合成
 */
void wavegen_init()
{
  HAL_TIM_Base_Start(&ddstim_dev);
}

/**
 * 根据收到的数据合成频率（小端格式，最低位代表最低频点）
 */
void wavegen_synthesize(uint8_t data)
{
  lut_index_t acc; /* 相位累加值 */
  uint8_t mask = 1;
  int freq_points = 0;

  for (int i = 0; i < OUTPUT_BUFLEN; ++i)
  {
    dac_buf[i] = 2048;
  }

  for (int freq_ix = 0; freq_ix < FREQ_POINTS; ++freq_ix)
  {
    if (mask & data)
    {
      acc = 0;
      freq_points++;
      mask = mask << 1;
      for (int i = 0; i < OUTPUT_BUFLEN; ++i)
      {
        dac_buf[i] += get_lut_data(acc);
        acc = (acc + ftw[freq_ix]) % PHASE_ACC_MAX;
      }
    }
  }

  for (int i = 0; i < OUTPUT_BUFLEN; ++i)
    dac_buf[i] /= freq_points;

  HAL_DAC_Stop_DMA(&dac_dev, DAC_CHANNEL_1);
  HAL_DAC_Start_DMA(&dac_dev, DAC_CHANNEL_1,
    (uint32_t *)dac_buf, OUTPUT_BUFLEN, DAC_ALIGN_12B_R);

  delay_ms(3);
  HAL_DAC_Stop_DMA(&dac_dev, DAC_CHANNEL_1);
}

void wavegen_freq_d()
{
  lut_index_t acc = 0;

  for (int i = 0; i < OUTPUT_BUFLEN; ++i)
  {
    dac_buf[i] = 2048;
  }

  for (int i = 0; i < OUTPUT_BUFLEN; ++i)
  {
    dac_buf[i] += get_lut_data(acc);
    acc = (acc + FTW_D) % PHASE_ACC_MAX;
  }

  HAL_DAC_Start_DMA(&dac_dev, DAC_CHANNEL_1,
    (uint32_t *)dac_buf, OUTPUT_BUFLEN, DAC_ALIGN_12B_R);
}