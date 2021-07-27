#ifndef __RECEIVER_H
#define __RECEIVER_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "usart.h"

#define recv_dev    huart3

/**
 * 准备好接收电脑端的数据
 */
void receiver_init();

/**
 * UART接收回调函数
 */
void receiver_recv_cb();

/**
 * 主循环中调用，检测数据并处理
 */
void receiver_data_process();

#ifdef  __cplusplus
}
#endif
#endif /* __RECEIVER_H */
