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


uint8_t WarningNowStatus=0;
uint8_t WarningPastStatus=0;
uint8_t WarningStatus=0;
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
    Warning_Enable_Num(2);
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
        beep_start(0,1);//红灯,蜂鸣器三下
        loss_led_start();
        LOG_D("MasterLostPeakWarning\r\n");
        break;
    case 2://测水线短路
        Warning_Enable_Num(4);
        break;
    case 3://测水线短路解除
        MasterStatusChangeToDeAvtive();
        break;
    }
}
void WaterScan_Clear(void)
{
    WarningPastStatus=0;
    WarningNowStatus=0;
    WarningStatus = 0;
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
            WarningNowStatus=1;//测水线掉落
            LOG_D("Peak_Loss is active\r\n");
        }
        else
        {
            if(Peak_ON_Level==0)
            {
                WarningNowStatus=2;//测水线短路
                LOG_D("Peak_ON is active\r\n");
            }
            else WarningNowStatus=0;//状态正常
        }
        if(WarningNowStatus != WarningPastStatus)
        {
            if(WarningPastStatus==2 && WarningNowStatus==0)
            {
                if(WarningStatus != 1<<0)
                {
                    WarningStatus = 1<<0;
                    WarningWithPeak(3);
                    LOG_D("Change Status to Deactive\r\n");
                }
            }
            else if(WarningPastStatus==2 && WarningNowStatus==1)
            {
                if(WarningStatus != 1<<1)
                {
                    WarningStatus = 1<<1;
                }
            }
            else if(WarningPastStatus==0 && WarningNowStatus==1)
            {
                if(WarningStatus != 1<<2)
                {
                    WarningPastStatus = WarningNowStatus;
                    WarningStatus = 1<<2;
                    WarningWithPeak(1);
                }
            }
            else if(WarningPastStatus==0 && WarningNowStatus==2)
            {
                if(WarningStatus != 1<<3)
                {
                    WarningPastStatus = WarningNowStatus;
                    WarningStatus = 1<<3;
                    WarningWithPeak(2);
                }
            }
            else if(WarningPastStatus==1 && WarningNowStatus==0)
            {
                if(WarningStatus != 1<<4)
                {
                    WarningPastStatus = WarningNowStatus;
                    WarningStatus = 1<<4;
                    WarningWithPeak(0);
                }
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
