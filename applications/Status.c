/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-11-27     Rick       the first version
 */
#include <rtthread.h>
#include "pin_config.h"
#include "key.h"
#include "led.h"
#include "status.h"
#include "flashwork.h"
#include "radio_encoder.h"
#include "Moto.h"
#include "work.h"

#define DBG_TAG "status"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

extern enum Device_Status Now_Status;
extern uint8_t ValveStatus;
extern uint16_t Radio_Counter;

void SlaverLowBatteryWarning(void)
{
    Moto_Close(NormalOff);
    beep_start(0,0);//红灯,蜂鸣器一下
    Now_Status = SlaverLowPower;
    LOG_D("SlaverLowBatteryWarning\r\n");
}
MSH_CMD_EXPORT(SlaverLowBatteryWarning,SlaverLowBatteryWarning);
void SlaverWaterAlarmWarning(void)
{
    Moto_Close(NormalOff);
    beep_start(0,2);//红灯,蜂鸣器三下
    Now_Status = SlaverWaterAlarmActive;
    LOG_D("SlaverWaterAlarmWarning\r\n");
}
MSH_CMD_EXPORT(SlaverWaterAlarmWarning,SlaverWaterAlarmWarning);
void MasterLostPeakWarning(void)
{
    //Moto_Close();
    beep_start(0,1);//红灯,蜂鸣器二下
    Now_Status = MasterLostPeak;
    LOG_D("MasterLostPeakWarning\r\n");
}
MSH_CMD_EXPORT(MasterLostPeakWarning,MasterLostPeakWarning);
void MasterWaterAlarmWarning(void)
{
    beep_start(0,2);//红灯,蜂鸣器三下
    Moto_Close(NormalOff);
    if(GetDoorID())
    {
        RadioEnqueue(1,GetDoorID(),Radio_Counter+1,4,1);
    }
    Now_Status = MasterWaterAlarmActive;
    LOG_D("MasterWaterAlarmWarning\r\n");
}
MSH_CMD_EXPORT(MasterWaterAlarmWarning,MasterWaterAlarmWarning);
void MasterAlarmWaterDisable(void)
{
    if(GetDoorID())
    {
        RadioEnqueue(1,GetDoorID(),Radio_Counter+1,4,0);
    }
}
void OfflineWarning(void)
{
    if(Now_Status!=Offline)
    {
        Moto_Close(NormalOff);
        beep_start(0,5);
        Now_Status = Offline;
        LOG_D("OfflineWarning\r\n");
    }
    else
    {
        LOG_D("Already OfflineWarning Now\r\n");
    }

}
void BackToNormal(void)
{
    WaterScan_Clear();
    beep_stop();
    led_Stop(0);
    //led_Stop(1);
//    if(ValveStatus)
//    {
//        Moto_Open(NormalOpen);
//    }
//    else
//    {
//        Moto_Close(NormalOff);
//    }
}

