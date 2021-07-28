#ifndef __LISTEN_H
#define __LISTEN_H

#ifdef  __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "adc.h"

#define adc_dev       hadc1
#define adc_dma_dev   hdma_adc1

#define FREQ_1      4000
#define FREQ_2      8000
#define FREQ_3      12000
#define FREQ_4      19000
#define FREQ_D      30000

void wait_for_signal();

uint8_t decode_signal();

extern DMA_HandleTypeDef hdma_adc1;

#ifdef  __cplusplus
}
#endif
#endif /* __LISTEN_H */
