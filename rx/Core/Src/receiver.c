#include "receiver.h"
#include "queue.h"
#include "tty.h"

static uint8_t recv_data;

/**
 * 准备好接收电脑端的数据
 */
void receiver_init()
{
  queue_reset();
  HAL_UART_Receive_IT(&recv_dev, &recv_data, 1);
}

/**
 * UART接收回调函数
 */
void receiver_recv_cb()
{
  queue_push(recv_data);
  HAL_UART_Receive_IT(&recv_dev, &recv_data, 1);
}

/**
 * 主循环中调用，检测数据并处理
 */
void receiver_data_process()
{
  static uint8_t data;
  if (queue_pop(&data) > 0)
  {
    tty_print("%c", data);
  }
}