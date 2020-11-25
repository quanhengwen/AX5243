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
#include "beep.h"
#include "device.h"
#include "led.h"
#include "work.h"
#include "fal.h"
#include "easyflash.h"

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>
void boot_time(void)
{
    uint32_t i_boot_times = 0;
    char *c_old_boot_times, c_new_boot_times[11] = {0};

    /* 从环境变量中获取启动次数 */
    c_old_boot_times = ef_get_env("boot_times");
    /* 获取启动次数是否失败 */
    if (c_old_boot_times == RT_NULL)
        c_old_boot_times[0] = '0';

    i_boot_times = atol(c_old_boot_times);
    /* 启动次数加 1 */
    i_boot_times++;
    LOG_D("===============================================");
    LOG_D("The system now boot %d times", i_boot_times);
    LOG_D("===============================================");
    /* 数字转字符串 */
    sprintf(c_new_boot_times, "%d", i_boot_times);
    /* 保存开机次数的值 */
    ef_set_env("boot_times", c_new_boot_times);
    ef_save_env();
}
int main(void)
{
    fal_init();
    easyflash_init();
    boot_time();
    beep_user_Init();
    button_Init();
    led_Init();
    WaterScan_Init();
    Radio_Task_Init();
    while (1)
    {
        rt_thread_mdelay(1000);
    }
    return RT_EOK;
}
