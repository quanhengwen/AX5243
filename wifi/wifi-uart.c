/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-12-21     Rick       the first version
 */
#include "rtthread.h"
#include "rtdevice.h"
#include "pin_config.h"
#include "wifi-uart.h"
#include "ulog.h"
#include "wifi.h"
#include "wifi-service.h"

/* 用于接收消息的信号量 */
static struct rt_semaphore rx_sem;
static rt_device_t serial;
static rt_thread_t WiFi_Uart_Thread = RT_NULL;
struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;  /* 初始化配置参数 */

#define WiFi_UART_NAME                   "uart1"


#define DBG_TAG "wifi_uart"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

void wifi_gpio_enable(void)
{
    rt_pin_mode(WIFIEN,PIN_MODE_OUTPUT);
    rt_pin_write(15,1);
}
/* 接收数据回调函数 */
static rt_err_t uart_rx_ind(rt_device_t dev, rt_size_t size)
{
    /* 串口接收到数据后产生中断，调用此回调函数，然后发送接收信号量 */
    if (size > 0)
    {
        rt_sem_release(&rx_sem);
    }
    return RT_EOK;
}

static char uart_sample_get_char(void)
{
    char ch;

    while (rt_device_read(serial, 0, &ch, 1) == 0)
    {
        rt_sem_control(&rx_sem, RT_IPC_CMD_RESET, RT_NULL);
        rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
    }
    return ch;
}
/* 数据解析线程 */
void data_parsing(void)
{
    char ch;
    LOG_D("WiFi-Uart Init Success\r\n");

    while (1)
    {
        ch = uart_sample_get_char();
        uart_receive_input(ch);
        //LOG_D("GET Data is %X\r\n",ch);
    }
}
void WiFi_Byte_Send(uint8_t data)
{
    //LOG_D("Data %X is Send OK\r\n",data);
    rt_device_write(serial,0,&data,1);
}
void wifi_uart_init(void)
{
    char uart_name[RT_NAME_MAX];

    rt_strncpy(uart_name, WiFi_UART_NAME, RT_NAME_MAX);

    /* 查找系统中的串口设备 */
    serial = rt_device_find(uart_name);
    if (!serial)
    {
        LOG_D("find %s failed!\n", uart_name);
    }

    /* 初始化信号量 */
    rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
    /* 串口参数配置 */
    config.baud_rate = BAUD_RATE_115200;        //修改波特率为 115200
    config.data_bits = DATA_BITS_8;           //数据位 8
    config.stop_bits = STOP_BITS_1;           //停止位 1
    config.bufsz     = 128;                   //修改缓冲区 buff size 为 128
    config.parity    = PARITY_NONE;           //无奇偶校验位
    rt_device_control(serial, RT_DEVICE_CTRL_CONFIG, &config);
    /* 以中断接收及轮询发送模式打开串口设备 */
    rt_device_open(serial, RT_DEVICE_FLAG_INT_RX);
    /* 设置接收回调函数 */
    rt_device_set_rx_indicate(serial, uart_rx_ind);

    /* 创建 serial 线程 */
    WiFi_Uart_Thread = rt_thread_create("serial", (void (*)(void *parameter))data_parsing, RT_NULL, 1024, 25, 10);

    /* 创建成功则启动线程 */
    if (WiFi_Uart_Thread != RT_NULL)
    {
        rt_thread_startup(WiFi_Uart_Thread);
    }
}
MSH_CMD_EXPORT(wifi_uart_init, wifi_uart_init);
void WiFi_Init(void)
{
    uint8_t i=10;
    wifi_gpio_enable();
    wifi_uart_init();
    wifi_protocol_init();
    wifi_service_init();
//    mcu_reset_wifi();
//    while(mcu_get_reset_wifi_flag()==0&&i--)
//    {
//        LOG_D("Try to reset Wifi,Counter is %d\r\n",i);
//        rt_thread_mdelay(1000);
//    }
//    i=10;
//    mcu_set_wifi_mode(0);
//    while(mcu_get_wifimode_flag()==0&&i--)
//    {
//        LOG_D("Try to Init Wifi,Counter is %d\r\n",i);
//        rt_thread_mdelay(1000);
//    }
    if(i>0)
    {
        LOG_D("Wifi Init Success\r\n");
    }
    else
    {
        LOG_D("Wifi Init Fail\r\n");
    }
}
