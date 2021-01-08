/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-11-25     Rick       the first version
 */
#include <rtthread.h>
#include "pin_config.h"
#include "key.h"
#include "led.h"
#include "moto.h"
#include "Radio_Decoder.h"
#include "work.h"
#include "status.h"
#include "flashwork.h"
#include "rthw.h"

#define DBG_TAG "key"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

rt_thread_t key_response_t = RT_NULL;

uint8_t K0_Status=0;
uint8_t K0_Long_Status=0;
uint8_t K1_Status=0;
uint8_t K1_Long_Status=0;
uint8_t K0_K1_Status=0;
uint8_t ValveStatus = 0;

extern rt_sem_t K0_Sem;
extern rt_sem_t K0_Long_Sem;
extern rt_sem_t K1_Sem;
extern rt_sem_t K1_Long_Sem;
extern rt_sem_t K0_K1_Long_Sem;

extern uint8_t Learn_Flag;
extern uint8_t Last_Close_Flag;

rt_timer_t Learn_Timer;

enum Device_Status Now_Status=Close;
void Key_Reponse_Callback(void *parameter)
{
    LOG_D("Key_Reponse Init Success\r\n");
    while(1)
    {
        K0_Status = rt_sem_take(K0_Sem, 0);
        K0_Long_Status = rt_sem_take(K0_Long_Sem, 0);
        K1_Status = rt_sem_take(K1_Sem, 0);
        K1_Long_Status = rt_sem_take(K1_Long_Sem, 0);
        K0_K1_Status = rt_sem_take(K0_K1_Long_Sem, 0);
        if(K0_Status==RT_EOK)//ON
        {
            switch(Now_Status)
            {
            case Close:
                if(Last_Close_Flag==0)
                {
                    key_down();
                    Moto_Open(NormalOpen);
                }
                else
                {
                    beep_start(0,7);//蜂鸣器三下
                }
                LOG_D("Valve Open With ON\r\n");
                break;
            case Open:
                key_down();
                LOG_D("Valve Already Open With ON\r\n");
                break;
            case SlaverLowPower:
                break;
            case SlaverWaterAlarmActive:
                break;
            case MasterLostPeak:
                key_down();
                Now_Status = Open;
                Moto_Open(NormalOpen);
                LOG_D("MasterLostPeak With ON\r\n");
                break;
            case MasterWaterAlarmActive:
                beep_start(0,2);
                LOG_D("MasterWaterAlarmActive With ON\r\n");
                break;
            case Learn:
                break;
            case Offline:
                break;
            }
        }
        else if(K1_Status==RT_EOK)//OFF
        {
            switch(Now_Status)
            {
            case Close:
                if(Last_Close_Flag==0)
                {
                    key_down();
                }
                else
                {
                    beep_start(0,7);//蜂鸣器三下
                }
                //Last_Close_Flag = 0;
                LOG_D("Valve Already Close With OFF\r\n");
                break;
            case Open:
                key_down();
                Last_Close_Flag = 0;
                Moto_Close(NormalOff);
                LOG_D("Valve Close With OFF\r\n");
                break;
            case SlaverLowPower:
                break;
            case SlaverWaterAlarmActive:
                break;
            case MasterLostPeak:
                key_down();
                Now_Status = Close;
                Disable_Warining();//消警
                LOG_D("MasterLostPeak With OFF\r\n");
                break;
            case MasterWaterAlarmActive:
                Now_Status = Close;
                Disable_Warining();//消警
                key_down();
                MasterAlarmWaterDisable();
                LOG_D("MasterWaterAlarmActive With OFF\r\n");
                break;
            case Learn:
                break;
            case Offline:
                break;
            }
        }
        else if(K0_K1_Status==RT_EOK)
        {
            DeleteAllDevice();
            beep_start(0,8);//蜂鸣器5次
            rt_thread_mdelay(2500);
            rt_hw_cpu_reset();
        }
        else if(K1_Long_Status==RT_EOK)//OFF
        {
            if(Now_Status==Close||Now_Status==Open)
            {
                Now_Status = Learn;
                Start_Learn_Key();
            }
            else if(Now_Status==Learn)
            {
                Stop_Learn();
            }
            else
            {
                LOG_D("Now in Warining Mode\r\n");
            }
        }
        rt_thread_mdelay(20);
    }
}
void statusread(void)
{
    LOG_D("Now Status is %d\r\n",Now_Status);
}
MSH_CMD_EXPORT(statusread,statusread);
void Learn_Timer_Callback(void *parameter)
{
    LOG_D("Learn timer is Timeout\r\n");
    Disable_Warining();//消警
    Stop_Learn();
}
void Key_Reponse(void)
{
    key_response_t = rt_thread_create("key_response_t", Key_Reponse_Callback, RT_NULL, 1024, 10, 10);
    if(key_response_t!=RT_NULL)rt_thread_startup(key_response_t);
    Learn_Timer = rt_timer_create("Learn_Timer", Learn_Timer_Callback, RT_NULL, 60*1000, RT_TIMER_FLAG_ONE_SHOT|RT_TIMER_FLAG_SOFT_TIMER );
}
