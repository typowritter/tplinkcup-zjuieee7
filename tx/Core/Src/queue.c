/**
  ******************************************************************************
  * @file    queue.c
  * @author  yxnan <yxnan@pm.me>
  * @date    2021-07-27
  * @brief   流数据队列实现
  ******************************************************************************
  */

#include "queue.h"

#define QUEUE_MAX_SIZE 20  /* 电脑端下行比特数不超过160 */

static struct
{
  qsize_t head;
  qsize_t tail;
  qdata_t data[QUEUE_MAX_SIZE];
} g_queue;

/**
 * 清空指令数据
 */
void queue_reset()
{
  g_queue.head = g_queue.tail = 0;
}

/**
 * UART接收的数据，通过此函数放入指令队列
 */
void queue_push(qdata_t data)
{
  qsize_t pos = (g_queue.head + 1) % QUEUE_MAX_SIZE;

  if (pos != g_queue.tail)          /* 非满状态 */
  {
    g_queue.data[g_queue.head] = data;
    g_queue.head = pos;
  }
}

/**
 * 从队列中取出一个数据
 *
 * @return  -- 1: 队列非空，数据有效
 *          -- 0: 队列为空，数据无效
 */
qsize_t queue_pop(qdata_t *data)
{
  if (g_queue.tail != g_queue.head)  /* 非空状态 */
  {
    *data = g_queue.data[g_queue.tail];
    g_queue.tail = (g_queue.tail + 1) % QUEUE_MAX_SIZE;
    return 1;
  }
  return 0;
}

/**
 * 获取队列中有效数据个数
 */
qsize_t queue_size()
{
  return (g_queue.head + QUEUE_MAX_SIZE - g_queue.tail) % QUEUE_MAX_SIZE;
}
