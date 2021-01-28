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
#include "RTCWork.h"
#include "status.h"
#include "dog.h"
#include "radio_decoder.h"

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

int main(void)
{
    if(Factory_Detect())
    {
        led_Init();
        wdt_sample();
        Radio_Task_Init();
        Factory_Test();
    }
    else
    {
        fal_init();
        easyflash_init();
        Boot_Times_Record();
        LoadDevice2Memory();
        WarningInit();
        led_Init();
        Moto_Init();
        button_Init();
        WaterScan_Init();
        Key_Reponse();
        Radio_Task_Init();
        //wdt_sample();
        RTC_Init();
        WiFi_Init();
    }

    while (1)
    {
        //FeedDog();
        rt_thread_mdelay(1000);
    }
    return RT_EOK;
}
