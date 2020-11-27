/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-11-27     Rick       the first version
 */
#ifndef APPLICATIONS_STATUS_H_
#define APPLICATIONS_STATUS_H_
void SlaverLowBatteryWarning(void);
void SlaverWaterAlarmWarning(void);
void MasterLostPeakWarning(void);
void MasterWaterAlarmWarning(void);
void BackToNormal(void);


#endif /* APPLICATIONS_STATUS_H_ */
