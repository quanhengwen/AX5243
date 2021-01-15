/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-29     Rick       the first version
 */
#ifndef APPLICATIONS_RTCWORK_H_
#define APPLICATIONS_RTCWORK_H_

void RTC_Init(void);
void RTC_Clear(void);
uint8_t Detect_RTC_Wakeup(void);
void RTC_Check(void);
void LowPowerTimerStart(void);

#endif /* APPLICATIONS_RTCWORK_H_ */
