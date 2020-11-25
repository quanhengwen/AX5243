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

#define DBG_TAG "key"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

rt_thread_t key_response_t = RT_NULL;
uint8_t K0_Status=0;
uint8_t K0_Long_Status=0;
uint8_t K1_Status=0;
uint8_t K1_Long_Status=0;

extern rt_sem_t K0_Sem;
extern rt_sem_t K0_Long_Sem;
extern rt_sem_t K1_Sem;
extern rt_sem_t K1_Long_Sem;

void Key_Reponse_Callback(void *parameter)
{
    LOG_D("Key_Reponse Init Success\r\n");
    while(1)
    {
        K0_Status = rt_sem_take(K0_Sem, 0);
        K0_Long_Status = rt_sem_take(K0_Long_Sem, 0);
        K1_Status = rt_sem_take(K1_Sem, 0);
        K1_Long_Status = rt_sem_take(K1_Long_Sem, 0);
        if(K0_Status==RT_EOK)
        {

        }
        else if(K1_Status==RT_EOK)
        {

        }
        else if(K0_Long_Status==RT_EOK)
        {

        }
        else if(K1_Long_Status==RT_EOK)
        {

        }
    }
}
void Key_Reponse(void)
{
    key_response_t = rt_thread_create("key_response_t", Key_Reponse_Callback, RT_NULL, 1024, 10, 10);
    if(key_response_t!=RT_NULL)rt_thread_startup(key_response_t);
}
