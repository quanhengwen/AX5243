/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-11-25     Rick       the first version
 */
#ifndef APPLICATIONS_KEY_H_
#define APPLICATIONS_KEY_H_
enum Device_Status
{
    Close=0,
    Open,
    SlaverLowPower,
    SlaverWaterAlarmActive,
    MasterLostPeak,
    MasterWaterAlarmActive,
    MasterWaterAlarmDeActive,
    Learn,
    Offline,
    WiFi
};
void Key_Reponse(void);


#endif /* APPLICATIONS_KEY_H_ */
