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

uint32_t Device_List[30]={20022636};
uint8_t Device_Num=1;
extern uint32_t Self_Id;

uint8_t Check_Valid(uint32_t From_id)
{
    for(uint8_t i=0;i<sizeof(Device_List);i++)
    {
        if(From_id == Device_List[i])
        {
            return 1;
        }
    }
   return 0;
}
void Device_Learn(Message buf)
{
//    if(buf.From_ID==99999999&&buf.Data==1)
//    {
//        LOG_D("Start Learn From %ld\r\n",buf.From_ID);
//    }
//    else
//    {
//        LOG_D("Not Include This Device\r\n");
//    }
//    switch(buf.Data)
//    {
//    case 3:
//    }
}
MSH_CMD_EXPORT(Device_Learn,Device_Learn);
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
            RadioSend(buf.From_ID,buf.Counter+1,2,0);
            LOG_D("Handshake With %ld\r\n",buf.From_ID);
        }
        else
        {
            LOG_D("Not Include This Device\r\n");
        }
        break;
    case 3://学习
        LOG_D("Learn\r\n");
        //Device_Learn();
        break;
    case 4://报警
        LOG_D("Warning\r\n");
        if(Check_Valid(buf.From_ID))
        {
            LOG_D("Warning From %ld\r\n",buf.From_ID);
            if(buf.Data==0)Disable_Warining();
            else Enable_Warining();
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
            LOG_D("Pwr On From %ld\r\n",buf.From_ID);
            RadioSend(buf.From_ID,buf.Counter+1,5,0);
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
            LOG_D("Pwr Off From %ld\r\n",buf.From_ID);
            RadioSend(buf.From_ID,buf.Counter+1,6,0);
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
        if(Rx_message.Target_ID==Self_Id)DataSolve(Rx_message);
    }
}
