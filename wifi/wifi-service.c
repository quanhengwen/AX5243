/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-30     Rick       the first version
 */
#include "rtthread.h"
#include "rtdevice.h"
#include "pin_config.h"
#include "wifi-uart.h"
#include "ulog.h"
#include "wifi.h"
#include "wifi-service.h"
#include "led.h"

#define DBG_TAG "wifi_service"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

static rt_thread_t WiFi_Service_Thread = RT_NULL;

void Show_WiFi(void)
{
    beep_start(0,10);//beep 5 times
    if(mcu_get_wifi_work_state()==0x03)
    {
        LOG_D("wifi is AP\r\n");
    }
    else
    {
        LOG_D("wifi is fail\r\n");
    }
}
MSH_CMD_EXPORT(Show_WiFi,Show_WiFi);
void Exit_WiFi(void)
{
    beep_start(0,11);//beep 3 times
}
MSH_CMD_EXPORT(Exit_WiFi,Exit_WiFi);
void Reset_WiFi(void)
{
    just_ring();
    mcu_reset_wifi();
    rt_thread_mdelay(500);
    if(mcu_get_reset_wifi_flag()==1)
    {
        LOG_D("Wifi Reset Success\r\n");
    }
    else
    {
        LOG_D("Wifi Reset Fail\r\n");
    }
}
MSH_CMD_EXPORT(Reset_WiFi,Reset_WiFi);
void service_callback(void *parameter)
{
    while(1)
    {
        wifi_uart_service();
        rt_thread_mdelay(5);
    }
}
void wifi_service_init(void)
{
    WiFi_Service_Thread = rt_thread_create("wifi-service", service_callback, RT_NULL, 2048, 10, 10);
    if(WiFi_Service_Thread!=RT_NULL)rt_thread_startup(WiFi_Service_Thread);
}
MSH_CMD_EXPORT(wifi_service_init,wifi_service_init);
