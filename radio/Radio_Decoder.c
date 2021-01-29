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
#include "pin_config.h"

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

uint8_t Learn_Flag=0;
uint8_t Last_Close_Flag=0;
uint16_t Radio_Counter=0;
uint8_t KidLock=0;

extern rt_timer_t Learn_Timer;
extern uint8_t ValveStatus ;
extern uint32_t Self_Id;
extern enum Device_Status Now_Status;

uint8_t Recv_Num;
rt_timer_t Factory_Test_Timer = RT_NULL;
void Factory_Test_Timer_Callback(void *parameter)
{
    if(Recv_Num>7)
    {
        led_on(1);
        LOG_D("Test is Success,Reselt is %d\r\n",Recv_Num);
    }
    else
    {
        led_on(0);
        LOG_D("Test is Failed,Reselt is %d\r\n",Recv_Num);
    }
}
uint8_t Factory_Detect(void)
{
    rt_pin_mode(TEST, PIN_MODE_INPUT_PULLUP);
    if(rt_pin_read(TEST)==0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void Factory_Test(void)
{
    Recv_Num = 0;
    Factory_Test_Timer = rt_timer_create("Factory_Test", Factory_Test_Timer_Callback, RT_NULL, 1000, RT_TIMER_FLAG_ONE_SHOT|RT_TIMER_FLAG_SOFT_TIMER);
    rt_timer_start(Factory_Test_Timer);
    LOG_D("Start Test\r\n");
}
MSH_CMD_EXPORT(Factory_Test,Factory_Test);
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
}
void Stop_Learn(void)
{
    Learn_Flag = 0;
    rt_timer_stop(Learn_Timer);
    Disable_Warining();//消警
    beep_start(0, 6);
    if(ValveStatus)Moto_Open(NormalOpen);else Moto_Close(NormalOff);
    LOG_D("Learn timer is stop\r\n");
}
void learn_test(void)
{
    Add_Device(20022636);
    Add_DoorDevice(33333333);
}
MSH_CMD_EXPORT(learn_test,learn_test);
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
                if(buf.From_ID<30000000)
                {
                    Add_Device(buf.From_ID);//向数据库写入
                    LOG_D("Slaver Write to Flash With ID %d\r\n",buf.From_ID);
                }
                else if(buf.From_ID>30000000 && buf.From_ID<40000000)
                {
                    Add_DoorDevice(buf.From_ID);//向数据库写入
                    LOG_D("Door Write to Flash With ID %d\r\n",buf.From_ID);
                }
            }
            else//存在该值
            {
                LOG_D("Include This Device，Send Ack\r\n");
            }
            RadioEnqueue(0,buf.From_ID,buf.Counter,3,1);
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
                just_ring();    //响一声
                RadioEnqueue(0,buf.From_ID,buf.Counter,3,2);
            }
        }
        else LOG_D("Not in Learn Mode\r\n");
        break;
    case 3:
        if(Check_Valid(buf.From_ID))//如果数据库不存在该值
        {
            Start_Learn();
            RadioEnqueue(0,buf.From_ID,buf.Counter,3,3);
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
        if(Check_Valid(buf.From_ID))
        {
            RadioEnqueue(0,buf.From_ID,buf.Counter,1,1);
        }
        LOG_D("Test\r\n");
        break;
    case 2://握手包
        LOG_D("HandShake\r\n");
        if(Check_Valid(buf.From_ID))
        {
            if(buf.Data==2)
            {
                RadioEnqueue(0,buf.From_ID,buf.Counter,2,2);
                Warning_Enable_Num(1);
                WariningUpload(buf.From_ID,1);
            }
            else
            {
                Update_Device_Bat(buf.From_ID,buf.Data);//写入电量
                RadioEnqueue(0,buf.From_ID,buf.Counter,2,0);
                //Disable_Warining();
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
                LOG_D("Warning With Command 4 Data 0\r\n");
                if(GetDoorID()==buf.From_ID)//是否为主控的回包
                {
                    LOG_D("RECV 40 From Door\r\n");
                }
                else//是否为来自终端的数据
                {
                    RadioEnqueue(0,buf.From_ID,buf.Counter,4,0);
                    if(GetDoorID())
                    {
                        RadioEnqueue(1,GetDoorID(),buf.Counter,4,0);
                    }
                }
            }
            else if(buf.Data==1)
            {
                LOG_D("Warning With Command 4 Data 1\r\n");
                if(GetDoorID()==buf.From_ID)//是否为主控的回包
                {
                    LOG_D("RECV 41 From Door\r\n");
                }
                else//是否为来自终端的报警包
                {
                    RadioEnqueue(0,buf.From_ID,buf.Counter,4,1);
                    if(Now_Status!=SlaverWaterAlarmActive)
                    {
                        if(GetDoorID())
                        {
                            RadioEnqueue(1,GetDoorID(),buf.Counter,4,1);
                        }
                        Enable_Warining();
                        WariningUpload(buf.From_ID,2);
                    }
                }
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
            if((Now_Status==Open||Now_Status==Close||Now_Status==SlaverLowPower) && (Now_Status!=Offline))
            {
                LOG_D("Pwr On From %ld\r\n",buf.From_ID);
                //Disable_Warining();
                just_ring();
                Moto_Open(OtherOpen);
                Last_Close_Flag=0;
                RadioEnqueue(0,buf.From_ID,buf.Counter,5,1);
            }
            else
            {
                LOG_D("Pwr On From %ld On Warning\r\n",buf.From_ID);
                RadioEnqueue(0,buf.From_ID,buf.Counter,5,2);
            }
        }
        else
        {
            LOG_D("Not Include This Device\r\n");
        }
        break;
    case 6://关机
        LOG_D("Pwr Off and Now State is %d\r\n",Now_Status);
        if(Check_Valid(buf.From_ID))
        {
            if(Now_Status==Open||Now_Status==Close||Now_Status==SlaverLowPower)
            {
                LOG_D("Pwr Off From %ld\r\n",buf.From_ID);
                Disable_Warining();
                just_ring();
                Last_Close_Flag=1;
                Moto_Close(OtherOff);
                RadioEnqueue(0,buf.From_ID,buf.Counter,6,0);
            }
            else if(Now_Status == SlaverWaterAlarmActive)
            {
                LOG_D("Warning With Command 6\r\n");
                Disable_Warining();
                Moto_Close(OtherOff);
                RadioEnqueue(0,buf.From_ID,buf.Counter,6,0);
            }
        }
        else
        {
            LOG_D("Not Include This Device\r\n");
        }
        break;
    case 7://童锁
        LOG_D("Kid Lock!\r\n");
        if(Check_Valid(buf.From_ID))
        {
            if(GetDoorID()==buf.From_ID)//是否为主控的回包
            {
                LOG_D("RECV KidLock 7%d From Door\r\n",buf.Data);
                KidLock = buf.Data;
            }
        }
        else
        {
            LOG_D("Not Include This Device\r\n");
        }
        break;
    }
    if(buf.Counter==0)
    {
        ChangeMaxPower();
    }
    else
    {
        BackNormalPower();
    }
    Detect_All_TimeInDecoder(buf.From_ID);
    Check_Wor_Recv(buf.From_ID,buf.Command,buf.Data);
}
void status_serach(void)
{
    LOG_D("Status is %d\r\n",Now_Status);
}
MSH_CMD_EXPORT(status_serach,status_serach);
void Rx_Done_Callback(uint8_t *rx_buffer,uint8_t rx_len,int8_t rssi)
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
        if(Rx_message.From_ID == 10000001)
        {
            Recv_Num++;
        }
        if(Rx_message.Target_ID==Self_Id ||Rx_message.Target_ID==99999999)
        {
            DataSolve(Rx_message);
        }
        Radio_Counter = Rx_message.Counter;
        Update_Device_Rssi(Rx_message.From_ID,rssi);
    }

}
