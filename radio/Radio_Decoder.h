/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-11-22     Rick       the first version
 */
#ifndef RADIO_RADIO_DECODER_H_
#define RADIO_RADIO_DECODER_H_


void Rx_Done_Callback(uint8_t *rx_buffer,uint8_t rx_len,int8_t rssi);
void Start_Learn(void);
void Stop_Learn(void);
void Start_Learn_Key(void);
uint8_t Factory_Detect(void);
void Factory_Test(void);

#endif /* RADIO_RADIO_DECODER_H_ */
