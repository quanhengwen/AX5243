/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-11-22     Rick       the first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include <stm32f411xe.h>
#include "drv_spi.h"
#include <string.h>
#include "AX5043.h"
#include "Radio_Config.h"
#include "Radio.h"
#include "Radio_Decoder.h"
#include "Radio_Encoder.h"
#include "stdio.h"
#include "work.h"
#include "Flashwork.h"
#include "status.h"
#include "moto.h"
#include "led.h"
#include "key.h"

extern rt_timer_t Learn_Timer;
extern uint32_t Self_Id;

#define DBG_TAG "radio_decoder"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

typedef struct
{
    long Target_ID;
    long From_ID;
    int Counter;
    int Command ;
    int Data;
}Message;

uint32_t Device_List[30]={12345678};
uint8_t Device_Num=1;

extern enum Device_Status Now_Status;
extern uint8_t ValveStatus ;
uint8_t Learn_Flag=0;
uint8_t Last_Close_Flag=0;

uint8_t Check_Valid(uint32_t From_id)
{
    if(Flash_Get_Key_Valid(From_id)==1)return 0;
    else return 1;
}
void Start_Learn_Key(void)
{
    Now_Status = Learn;
    Learn_Flag = 1;
    beep_start(0, 4);
    rt_timer_start(Learn_Timer);
    LOG_D("Learn timer is start\r\n");
}
void Start_Learn(void)
{
    if(Now_Status==Close||Now_Status==Open)
    {
        Now_Status = Learn;
        Learn_Flag = 1;
        beep_start(0, 4);
        rt_timer_start(Learn_Timer);
        LOG_D("Learn timer is start\r\n");
    }
    else
    {
        LOG_D("Now in Warining Mode\r\n");
    }
//    else
//    {
//        rt_timer_stop(Learn_Timer);
//        Disable_Warining();//消警
//        //beep_stop();
//        Learn_Flag = 0;
//        LOG_D("Learn timer is stop\r\n");
//    }
}
void Stop_Learn(void)
{
    Learn_Flag = 0;
    rt_timer_stop(Learn_Timer);
    Disable_Warining();//消警
    beep_start(0, 6);
    if(ValveStatus)Moto_Open();else Moto_Close();
    //beep_stop();
    LOG_D("Learn timer is stop\r\n");
}
void Device_Learn(Message buf)
{
    switch(buf.Data)
    {
    case 1:
        if(Learn_Flag)
        {
            if(Check_Valid(buf.From_ID)!=1)//如果数据库不存在该值
            {
                LOG_D("Not Include This Device\r\n");
                Add_Device(buf.From_ID);//向数据库写入
                LOG_D("Write to Flash With ID %d\r\n",buf.From_ID);
            }
            else//存在该值
            {
                LOG_D("Include This Device，Send Ack\r\n");
            }
            RadioSend(buf.From_ID,buf.Counter,3,1);
        }
        else LOG_D("Not in Learn Mode\r\n");
        break;
    case 2:
        if(Learn_Flag)
        {
            if(Check_Valid(buf.From_ID)!=1)//如果数据库不存在该值
            {
                LOG_D("Ack Not Include This Device\r\n");
            }
            else//存在该值
            {
                LOG_D("Include This Device，Send Confirmed\r\n");
                RadioSend(buf.From_ID,buf.Counter,3,2);
                //rt_timer_start(Learn_Timer);
            }
        }
        else LOG_D("Not in Learn Mode\r\n");
        break;
    case 3:
        //Learn_Flag = 0;
        if(Check_Valid(buf.From_ID))//如果数据库不存在该值
        {
            Start_Learn();
            RadioSend(buf.From_ID,buf.Counter,3,3);
        }
        else LOG_D("Unknown Device Want to Learn\r\n");
        break;
    }
    rt_timer_start(Learn_Timer);
}
void DataSolve(Message buf)
{
    switch(buf.Command)
    {
    case 1://测试模拟报警（RESET）
        LOG_D("Test\r\n");
        break;
    case 2://握手包
        LOG_D("HandShake\r\n");
        if(Check_Valid(buf.From_ID))
        {
            if(buf.Data==2)
            {
                RadioSend(buf.From_ID,buf.Counter,2,2);//低电量报警
                SlaverLowBatteryWarning();
            }
            else
            {
                RadioSend(buf.From_ID,buf.Counter,2,0);//正常握手
                Disable_Warining();
                //Moto_Open();
            }
            LOG_D("Handshake With %ld\r\n",buf.From_ID);
        }
        else
        {
            LOG_D("Not Include This Device\r\n");
        }
        break;
    case 3://学习
        if(Learn_Flag||buf.Data==3)
        {
            LOG_D("Learn\r\n");
            //Disable_Warining();
            Device_Learn(buf);
        }
        else
        {
            LOG_D("LearnFlag is Zero\r\n");
        }
        break;
    case 4://报警
        LOG_D("Warning\r\n");
        if(Check_Valid(buf.From_ID))
        {
            LOG_D("Warning From %ld\r\n",buf.From_ID);
            if(buf.Data==0)
            {
                if(buf.Command == 4)
                {
                    LOG_D("Warning With Command 4\r\n");
                    RadioSend(buf.From_ID,buf.Counter,4,0);
                }
            }
            else
            {
                RadioSend(buf.From_ID,buf.Counter,4,1);
                Enable_Warining();
            }
        }
        else
        {
            LOG_D("Not Include This Device\r\n");
        }
        break;
    case 5://开机
        LOG_D("Pwr On\r\n");
        if(Check_Valid(buf.From_ID))
        {
            if((Now_Status==Open||Now_Status==Close) && (Now_Status!=Offline))
            {
                LOG_D("Pwr On From %ld\r\n",buf.From_ID);
                Disable_Warining();
                key_down();
                Moto_Open();
                RadioSend(buf.From_ID,buf.Counter,5,1);
            }
            else
            {
                LOG_D("Pwr On From %ld On Warning\r\n",buf.From_ID);
                RadioSend(buf.From_ID,buf.Counter,5,2);
            }
        }
        else
        {
            LOG_D("Not Include This Device\r\n");
        }
        break;
    case 6://关机
        LOG_D("Pwr Off\r\n");
        if(Check_Valid(buf.From_ID))
        {
            if(Now_Status==Open||Now_Status==Close)
            {
                LOG_D("Pwr Off From %ld\r\n",buf.From_ID);
                Disable_Warining();
                just_ring();
                Last_Close_Flag=1;
                Moto_Close();
                RadioSend(buf.From_ID,buf.Counter,6,0);
            }
            else if(Now_Status == SlaverWaterAlarmActive)
            {
                LOG_D("Warning With Command 6\r\n");
                Disable_Warining();
                RadioSend(buf.From_ID,buf.Counter,6,0);
            }
        }
        else
        {
            LOG_D("Not Include This Device\r\n");
        }
        break;
    }
}
void Rx_Done_Callback(uint8_t *rx_buffer,uint8_t rx_len)
{
    Message Rx_message;
    LOG_D("Recv ok\r\n");
    if(rx_buffer[rx_len-1]==0x0A&&rx_buffer[rx_len-2]==0x0D)
    {
        LOG_D("Rx verify ok\r\n");
        rx_buffer[rx_len-1]=0;
        rx_buffer[rx_len-2]=0;
        sscanf((const char *)&rx_buffer[1],"{%ld,%ld,%d,%d,%d}",&Rx_message.Target_ID,&Rx_message.From_ID,&Rx_message.Counter,&Rx_message.Command,&Rx_message.Data);
        Clear_Device_Time(Rx_message.From_ID);
        if(Rx_message.Target_ID==Self_Id ||Rx_message.Target_ID==99999999)DataSolve(Rx_message);
    }
}
