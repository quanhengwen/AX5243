/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-11-21     Rick       the first version
 */
#ifndef APPLICATIONS_LED_H_
#define APPLICATIONS_LED_H_
void led_Init(void);
void led_Slow_Start(uint8_t led_id,uint8_t count);
void led_Fast_Start(uint8_t led_id,uint8_t count);
void led_Stop(uint8_t led_id);

#endif /* APPLICATIONS_LED_H_ */
