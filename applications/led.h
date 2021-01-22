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
void led_Long_Start(uint8_t led_id);
void led_Slow_Start(uint8_t led_id,int count);
void led_Fast_Start(uint8_t led_id,int count);
void led_Stop(uint8_t led_id);
void beep_start(uint8_t led_id,int mode);
void beep_stop(void);
void key_down(void);
void just_ring(void);
void beeplive(void);
void beepback(void);
void loss_led_start(void);
void loss_led_stop(void);
void led_on(uint8_t id);

#endif /* APPLICATIONS_LED_H_ */
