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

#define DBG_TAG "key"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

rt_thread_t key_response_t = RT_NULL;
uint8_t K0_Status=0;
uint8_t K0_Long_Status=0;
uint8_t K1_Status=0;
uint8_t K1_Long_Status=0;
uint8_t ValveStatus = 0;

extern rt_sem_t K0_Sem;
extern rt_sem_t K0_Long_Sem;
extern rt_sem_t K1_Sem;
extern rt_sem_t K1_Long_Sem;

extern uint8_t Learn_Flag;

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
        if(K0_Status==RT_EOK)//ON
        {
            switch(Now_Status)
            {
            case Close:
                key_down();
                Now_Status = Open;
                Moto_Open();
                LOG_D("Valve Open With ON\r\n");
                break;
            case Open:
                key_down();
                LOG_D("Valve Already Open With ON\r\n");
                break;
            case SlaverLowPower:
                break;
            case SlaverWaterAlarmActive:
                key_down();
                Now_Status = Open;
                Moto_Open();
                beep_start(0,2);//蜂鸣器三下
                LOG_D("SlaverWaterAlarmActive With ON\r\n");
                break;
            case MasterLostPeak:
                key_down();
                Now_Status = Open;
                Moto_Open();
                LOG_D("MasterLostPeak With ON\r\n");
                break;
            case MasterWaterAlarmActive:
                break;
            }
        }
        else if(K1_Status==RT_EOK)//OFF
        {
            switch(Now_Status)
            {
            case Close:
                key_down();
                LOG_D("Valve Already Close With OFF\r\n");
                break;
            case Open:
                key_down();
                Now_Status = Close;
                Moto_Close();
                LOG_D("Valve Close With OFF\r\n");
                break;
            case SlaverLowPower:
                key_down();
                Now_Status = Close;
                Disable_Warining();//消警
                LOG_D("SlaverLowPower With OFF\r\n");
                break;
            case SlaverWaterAlarmActive:
                key_down();
                Now_Status = Close;
                Disable_Warining();//消警
                LOG_D("SlaverWaterAlarmActive With OFF\r\n");
                break;
            case MasterLostPeak:
                key_down();
                Now_Status = Close;
                Disable_Warining();//消警
                LOG_D("MasterLostPeak With OFF\r\n");
                break;
            case MasterWaterAlarmActive:
                key_down();
                Now_Status = Close;
                Disable_Warining();//消警
                LOG_D("MasterWaterAlarmActive With OFF\r\n");
                break;
            }
        }
        else if(K0_Long_Status==RT_EOK)
        {

        }
        else if(K1_Long_Status==RT_EOK)//OFF
        {
            Start_Learn();
        }
        rt_thread_mdelay(20);
    }
}
void Learn_Timer_Callback(void *parameter)
{
    LOG_D("Learn timer is Timeout\r\n");
    beep_stop();
    Learn_Flag = 0;

}
void Key_Reponse(void)
{
    key_response_t = rt_thread_create("key_response_t", Key_Reponse_Callback, RT_NULL, 1024, 10, 10);
    if(key_response_t!=RT_NULL)rt_thread_startup(key_response_t);
    Learn_Timer = rt_timer_create("Learn_Timer", Learn_Timer_Callback, RT_NULL, 30*1000, RT_TIMER_FLAG_ONE_SHOT|RT_TIMER_FLAG_SOFT_TIMER );
}
