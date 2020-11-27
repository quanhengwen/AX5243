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

extern uint8_t ValveStatus;
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
        rt_thread_mdelay(500);
    }
}
MSH_CMD_EXPORT(test_moto,test_moto);
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

