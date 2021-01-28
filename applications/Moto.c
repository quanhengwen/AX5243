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
#include "key.h"
#include "moto.h"
#include "flashwork.h"
#include "wifi-service.h"

#define DBG_TAG "moto"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

rt_timer_t Moto_Timer1,Moto_Timer2 = RT_NULL;
uint8_t Turn1_Flag,Turn2_Flag = 0;

extern uint8_t ValveStatus;
extern enum Device_Status Now_Status;
extern Device_Info Global_Device;

void motoread(void)
{
    LOG_D("Moto is %d\r\n",Global_Device.LastFlag);
}
MSH_CMD_EXPORT(motoread,motoread);
void Moto_InitOpen(uint8_t ActFlag)
{
    LOG_D("Moto Open Init Now is is %d , act is %d\r\n",Global_Device.LastFlag,ActFlag);
    if(Global_Device.LastFlag == OtherOff && ActFlag == OtherOpen)
    {
        LOG_D("Moto is Open\r\n");
        Now_Status = Open;
        led_Long_Start(1);//绿灯
        ValveStatus=1;
        Global_Device.LastFlag = ActFlag;
        Flash_Moto_Change(ActFlag);
        rt_pin_mode(Moto,0);
        rt_pin_write(Moto,1);
    }
    else if(Global_Device.LastFlag != OtherOff )
    {
        LOG_D("Moto is Open\r\n");
        Now_Status = Open;
        led_Long_Start(1);//绿灯
        ValveStatus=1;
        Global_Device.LastFlag = ActFlag;
        Flash_Moto_Change(ActFlag);
        rt_pin_mode(Moto,0);
        rt_pin_write(Moto,1);
    }
    else {
        beep_start(0,7);//蜂鸣器三下
        LOG_D("No permissions to Open\r\n");
    }
}
void Moto_Open(uint8_t ActFlag)
{
    LOG_D("Moto Open Now is is %d , act is %d\r\n",Global_Device.LastFlag,ActFlag);
    if(Global_Device.LastFlag == OtherOff && ActFlag == OtherOpen)
    {
        LOG_D("Moto is Open\r\n");
        Now_Status = Open;
        led_Long_Start(1);//绿灯
        ValveStatus=1;
        Global_Device.LastFlag = ActFlag;
        Flash_Moto_Change(ActFlag);
        rt_pin_mode(Moto,0);
        rt_pin_write(Moto,1);
        MotoUpload(1);
    }
    else if(Global_Device.LastFlag != OtherOff )
    {
        LOG_D("Moto is Open\r\n");
        Now_Status = Open;
        led_Long_Start(1);//绿灯
        ValveStatus=1;
        Global_Device.LastFlag = ActFlag;
        Flash_Moto_Change(ActFlag);
        rt_pin_mode(Moto,0);
        rt_pin_write(Moto,1);
        MotoUpload(1);
    }
    else {
        beep_start(0,7);//蜂鸣器三下
        LOG_D("No permissions to Open\r\n");
    }
}
void Moto_Close(uint8_t ActFlag)
{
    LOG_D("Moto Close Now is is %d , act is %d\r\n",Global_Device.LastFlag,ActFlag);
    if(Global_Device.LastFlag != OtherOff )
    {
        LOG_D("Moto is Close\r\n");
        Now_Status = Close;
        led_Stop(1);//绿灯
        ValveStatus=0;
        Global_Device.LastFlag = ActFlag;
        Flash_Moto_Change(ActFlag);
        rt_pin_mode(Moto,0);
        rt_pin_write(Moto,0);
        MotoUpload(0);
    }
    else if(Global_Device.LastFlag == OtherOff && ActFlag == OtherOff)
    {
        Now_Status = Close;
        beep_start(0,7);//蜂鸣器三下
        LOG_D("Moto is alreay otheroff\r\n");
    }
    else
    {
        beep_start(0,7);//蜂鸣器三下
        LOG_D("No permissions to Off\r\n");
    }
}
void Moto_OpenByWifi(void)
{
    LOG_D("Moto is OpenByWifi\r\n");
    Now_Status = Open;
    led_Long_Start(1);//绿灯
    ValveStatus=1;
    Global_Device.LastFlag = NormalOpen;
    Flash_Moto_Change(NormalOpen);
    rt_pin_mode(Moto,0);
    rt_pin_write(Moto,1);
    MotoUpload(1);
}
void Moto_CloseByWifi(void)
{
    LOG_D("Moto is CloseByWifi\r\n");
    Now_Status = Close;
    led_Stop(1);//绿灯
    ValveStatus=0;
    Global_Device.LastFlag = NormalOff;
    Flash_Moto_Change(NormalOff);
    rt_pin_mode(Moto,0);
    rt_pin_write(Moto,0);
    MotoUpload(0);
}
void Turn1_Edge_Callback(void *parameter)
{
    LOG_D("Turn1_Edge_Callback\r\n");
    Turn1_Flag = 1;
}
void Turn2_Edge_Callback(void *parameter)
{
    LOG_D("Turn2_Edge_Callback\r\n");
    Turn2_Flag = 1;
}
void Turn1_Timer_Callback(void *parameter)
{
    Moto_Open(NormalOpen);
    rt_pin_irq_enable(Turn1, PIN_IRQ_DISABLE);
    if(!Turn1_Flag)
    {
        LOG_D("Moto1 is Fail\r\n");
        beep_start(0,9);
        WariningUpload(0,6);
    }
}
void Turn2_Timer_Callback(void *parameter)
{
    Moto_Open(NormalOpen);
    rt_pin_irq_enable(Turn2, PIN_IRQ_DISABLE);
    if(!Turn2_Flag)
    {
        LOG_D("Moto2 is Fail\r\n");
        beep_start(0,9);
        WariningUpload(0,6);
    }
}
void Moto_Init(void)
{
    rt_pin_mode(Turn1,PIN_MODE_INPUT);
    rt_pin_mode(Turn2,PIN_MODE_INPUT);
    rt_pin_attach_irq(Turn1, PIN_IRQ_MODE_FALLING, Turn1_Edge_Callback, RT_NULL);
    rt_pin_attach_irq(Turn2, PIN_IRQ_MODE_FALLING, Turn2_Edge_Callback, RT_NULL);
    Moto_Timer1 = rt_timer_create("Moto_Timer1", Turn1_Timer_Callback, RT_NULL, 5100, RT_TIMER_FLAG_ONE_SHOT|RT_TIMER_FLAG_SOFT_TIMER);
    Moto_Timer2 = rt_timer_create("Moto_Timer2", Turn2_Timer_Callback, RT_NULL, 5000, RT_TIMER_FLAG_ONE_SHOT|RT_TIMER_FLAG_SOFT_TIMER);
    just_ring();
    if(Global_Device.LastFlag != OtherOff)
    {
        Moto_InitOpen(Global_Device.LastFlag);
    }
    else if(Global_Device.LastFlag == 0)
    {
        Global_Device.LastFlag = NormalOpen;
        Moto_InitOpen(NormalOpen);
    }
    LOG_D("Moto is Init,Flag is %d\r\n",Global_Device.LastFlag);
}

MSH_CMD_EXPORT(Moto_Init,Moto_Init);
void Moto_Detect(void)
{
    uint8_t ValveFuncFlag = ValveStatus;
    if(rt_pin_read(Turn1)==1&&ValveFuncFlag==1)
    {
        Turn1_Flag = 0;
        rt_pin_irq_enable(Turn1, PIN_IRQ_ENABLE);
        Moto_Close(NormalOff);
        rt_timer_start(Moto_Timer1);
    }
    if(rt_pin_read(Turn2)==1&&ValveFuncFlag==1)
    {
        Turn2_Flag = 0;
        rt_pin_irq_enable(Turn2, PIN_IRQ_ENABLE);
        Moto_Close(NormalOff);
        rt_timer_start(Moto_Timer2);
    }
}
MSH_CMD_EXPORT(Moto_Detect,Moto_Detect);
