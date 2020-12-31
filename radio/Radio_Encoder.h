/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-11-22     Rick       the first version
 */
#ifndef RADIO_RADIO_ENCODER_H_
#define RADIO_RADIO_ENCODER_H_

void Tx_Done_Callback(uint8_t *rx_buffer,uint8_t rx_len);
void RadioSend(uint32_t Taget_Id,uint8_t counter,uint8_t Command,uint8_t Data);
void WorSend(uint32_t Taget_Id,uint8_t counter,uint8_t Command,uint8_t Data);
void RadioEnqueue(uint32_t wor_flag,uint32_t Taget_Id,uint8_t counter,uint8_t Command,uint8_t Data);
void RadioDequeueTaskInit(void);

#endif /* RADIO_RADIO_ENCODER_H_ */
