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

#define DBG_TAG "wifi_service"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

static rt_thread_t WiFi_Service_Thread = RT_NULL;

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
