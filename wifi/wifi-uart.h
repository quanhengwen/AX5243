/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-12-21     Rick       the first version
 */
#ifndef WIFI_WIFI_UART_H_
#define WIFI_WIFI_UART_H_

void WiFi_Init(void);
void wifi_uart_init(void);
void wifi_gpio_enable(void);
void WiFi_Byte_Send(uint8_t data);

#endif /* WIFI_WIFI_UART_H_ */
