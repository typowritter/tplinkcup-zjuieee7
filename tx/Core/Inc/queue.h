/**
  ******************************************************************************
  * @file    queue.h
  * @author  yxnan <yxnan@pm.me>
  * @date    2021-07-27
  * @brief   流数据队列实现
  ******************************************************************************
  */

#ifndef __QUEUE_H
#define __QUEUE_H

#ifdef  __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef uint8_t  qdata_t;
typedef uint16_t qsize_t;

/**
 * 清空指令数据
 */
void queue_reset(void);

/**
 * UART接收的数据，通过此函数放入数据队列
 */
void queue_push(qdata_t data);

/**
 * 从队列中取出一个数据
 *
 * @return  -- 1: 队列非空，数据有效
 *          -- 0: 队列为空，数据无效
 */
qsize_t queue_pop(qdata_t *data);

/**
 * 获取队列中有效数据个数
 */
qsize_t queue_size();

#ifdef  __cplusplus
}
#endif
#endif /* __QUEUE_H */
