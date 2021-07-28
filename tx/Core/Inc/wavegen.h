#ifndef __WAVEGEN_H
#define __WAVEGEN_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "dac.h"

#define ddstim_dev    htim7
#define dac_dev       hdac

/**
 * 准备波形合成
 */
void wavegen_init();

/**
 * 根据收到的数据合成频率（小端格式，最低位代表最低频点）
 */
void wavegen_synthesize(uint8_t data);

#ifdef  __cplusplus
}
#endif
#endif /* __WAVEGEN_H */
