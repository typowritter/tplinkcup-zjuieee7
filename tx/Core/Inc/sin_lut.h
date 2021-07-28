/**
  ******************************************************************************
  * @file    sin_lut.h
  * @author  yxnan@pm.me
  * @date    2021-07-27
  * @brief   采样率200kHz，深度11位的正弦查找表（仅前四分之一周期）
  ******************************************************************************
  */

#ifndef __SIN_LUT_H
#define __SIN_LUT_H

#ifdef  __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define DDS_SAMPLE_FREQ  300000
#define PHASE_ACC_DEPTH  11
#define PHASE_ACC_MAX    2048

typedef uint16_t lut_index_t;
typedef uint16_t dac_data_t;

dac_data_t get_lut_data(lut_index_t acc);

extern const dac_data_t sinelut_512[];

#ifdef  __cplusplus
}
#endif
#endif /* __SIN_LUT_H */
