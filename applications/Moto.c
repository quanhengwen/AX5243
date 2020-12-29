/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-11-27     Rick       the first version
 */
#include "rtthread.h"
#include "rtdevice.h"
#include "pin_config.h"
#include "led.h"

#define DBG_TAG "moto"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

rt_timer_t Moto_Timer1,Moto_Timer2 = RT_NULL;
uint8_t Turn1_Flag,Turn2_Flag = 0;
extern uint8_t ValveStatus;

void Moto_Open(void)
{
    LOG_D("Moto is Open\r\n");
    led_Long_Start(1);//绿灯
    ValveStatus=1;
    rt_pin_mode(Moto,0);
    rt_pin_write(Moto,1);
}
void Moto_Close(void)
{
    LOG_D("Moto is Close\r\n");
    led_Stop(1);//绿灯
    ValveStatus=0;
    rt_pin_mode(Moto,0);
    rt_pin_write(Moto,0);
}
void Turn1_Edge_Callback(void *parameter)
{
    Turn1_Flag = 1;
}
void Turn2_Edge_Callback(void *parameter)
{
    Turn2_Flag = 1;
}
void Turn1_Timer_Callback(void *parameter)
{
    Moto_Open();
    if(Turn1_Flag)
    {
        //上报
    }
}
void Turn2_Timer_Callback(void *parameter)
{
    Moto_Open();
    if(Turn2_Flag)
    {
        //上报
    }
}
void Moto_Init(void)
{
    rt_pin_mode(Turn1,PIN_MODE_INPUT);
    rt_pin_mode(Turn2,PIN_MODE_INPUT);
    rt_pin_attach_irq(Turn1, PIN_IRQ_MODE_FALLING, Turn1_Edge_Callback, RT_NULL);
    rt_pin_attach_irq(Turn2, PIN_IRQ_MODE_FALLING, Turn2_Edge_Callback, RT_NULL);
    rt_pin_irq_enable(Turn1, PIN_IRQ_ENABLE);
    rt_pin_irq_enable(Turn2, PIN_IRQ_ENABLE);
    LOG_D("Moto is Init\r\n");
    Moto_Timer1 = rt_timer_create("Moto_Timer1", Turn1_Timer_Callback, RT_NULL, 5000, RT_TIMER_FLAG_ONE_SHOT|RT_TIMER_FLAG_SOFT_TIMER);
    Moto_Timer2 = rt_timer_create("Moto_Timer2", Turn2_Timer_Callback, RT_NULL, 5000, RT_TIMER_FLAG_ONE_SHOT|RT_TIMER_FLAG_SOFT_TIMER);
}


void Moto_Detect(void)
{
    if(Turn1==1&&ValveStatus==1)
    {
        Turn1_Flag = 0;
        Moto_Close();
        rt_timer_start(Moto_Timer1);
    }
    if(Turn2&&ValveStatus==1)
    {
        Turn1_Flag = 0;
        Moto_Close();
        rt_timer_start(Moto_Timer2);
    }
}
void test_moto(void)//打开turn1高，关闭turn0高
{
    rt_pin_mode(Moto,0);
    rt_pin_mode(Turn1,1);
    rt_pin_mode(Turn2,1);
    rt_pin_write(Moto,1);
    while(1)
    {
        rt_kprintf("Turn1 is %d\r\n",rt_pin_read(Turn1));
        rt_kprintf("Turn2 is %d\r\n",rt_pin_read(Turn2));
        rt_kprintf("Senor1 is %d\r\n",rt_pin_read(Turn1));
        rt_kprintf("Senor2 is %d\r\n",rt_pin_read(Turn2));
        rt_thread_mdelay(1000);
    }
}
MSH_CMD_EXPORT(test_moto,test_moto);
