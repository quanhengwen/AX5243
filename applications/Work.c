/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-11-22     Rick       the first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include "device.h"
#include "led.h"
#include "work.h"
#include "pin_config.h"
#include "led.h"
#include "status.h"
#include "moto.h"
#include "Flashwork.h"

#define DBG_TAG "work"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>


uint8_t WarningStatus=0;
uint8_t WarningStatus_Temp=0;
uint8_t ValvePastStatus=0;
rt_thread_t WaterScan_t=RT_NULL;
extern uint8_t ValveStatus;

void Disable_Warining(void)
{
    BackToNormal();
    LOG_D("Warning is Close\r\n");
}
void Enable_Warining(void)
{
    SlaverWaterAlarmWarning();
    LOG_D("Warning is Open\r\n");
}
void WarningWithPeak(uint8_t status)
{
    switch(status)
    {
    case 0://恢复正常
        BackToNormal();
        beep_stop();
        loss_led_stop();
        break;
    case 1://测水线掉落
        MasterLostPeakWarning();
        break;
    case 2://测水线短路
        MasterWaterAlarmWarning();
        break;
    }
}
void WaterScan_Clear(void)
{
    WarningStatus=0;
    WarningStatus_Temp=0;
}
void WaterScan_Callback(void *parameter)
{
    uint8_t Peak_ON_Level=0;
    uint8_t Peak_Loss_Level=0;

    LOG_D("WaterScan Init Success\r\n");
    rt_pin_mode(Peak_ON,PIN_MODE_INPUT);
    rt_pin_mode(Peak_Loss,PIN_MODE_INPUT);
    while(1)//插入是0，短路是0
    {
        Peak_ON_Level = rt_pin_read(Peak_ON);
        Peak_Loss_Level = rt_pin_read(Peak_Loss);
        if(Peak_Loss_Level!=0)
        {
            WarningStatus_Temp=1;//测水线掉落
            LOG_D("Peak_Loss is active\r\n");
        }
        else
        {
            if(Peak_ON_Level==0)
            {
                WarningStatus_Temp=2;//测水线短路
                LOG_D("Peak_ON is active\r\n");
            }
            else WarningStatus_Temp=0;//状态正常
        }
        if(WarningStatus_Temp!=WarningStatus)
        {
            if(WarningStatus_Temp==0&&WarningStatus==2)
            {
                WarningStatus = WarningStatus_Temp;
                //MasterAlarmWaterDisable();
                LOG_D("Warning But Not Reponse\r\n");
            }
            else
            {
                WarningStatus = WarningStatus_Temp;
                LOG_D("Warning\r\n");
                WarningWithPeak(WarningStatus);
                //执行警报触发程序
            }
        }
        rt_thread_mdelay(500);
    }
}
void WaterScan_Init(void)
{
    WaterScan_t = rt_thread_create("WaterScan", WaterScan_Callback, RT_NULL, 1004, 30, 10);
    if(WaterScan_t!=RT_NULL)rt_thread_startup(WaterScan_t);
}
void AliveIncrease(void)//心跳使counter增加
{
    Update_All_Time();
}
void AliveDetect(void)//counter检测
{
    Update_All_Time();
}
