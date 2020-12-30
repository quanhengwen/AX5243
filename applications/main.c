/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-11-14     RT-Thread    first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "radio.h"
#include "radio_config.h"
#include "ax5043.h"
#include "device.h"
#include "led.h"
#include "work.h"
#include "fal.h"
#include "easyflash.h"
#include "flashwork.h"
#include "key.h"
#include "wifi-uart.h"
#include "moto.h"

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

int main(void)
{
    fal_init();
    easyflash_init();
    Boot_Times_Record();
    button_Init();
    led_Init();
    WaterScan_Init();
    Key_Reponse();
    LoadDevice2Memory();
    Radio_Task_Init();
    Moto_Init();
    WiFi_Init();
    while (1)
    {
        rt_thread_mdelay(1000);
    }
    return RT_EOK;
}
