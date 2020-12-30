/**********************************Copyright (c)**********************************
**                       版权所有 (C), 2015-2020, 涂鸦科技
**
**                             http://www.tuya.com
**
*********************************************************************************/
/**
 * @file    wifi.h
 * @author  涂鸦综合协议开发组
 * @version v1.0.6
 * @date    2020.11.11
 * @brief   用户无需关心该文件实现内容
 */


#include "cJSON.h"
#include <stdlib.h>
#include <stdio.h>
#ifndef __WIFI_H_
#define __WIFI_H_

//=============================================================================
/*定义常量*/
//=============================================================================
#ifndef TRUE
#define         TRUE                1
#endif

#ifndef FALSE
#define         FALSE               0
#endif

#ifndef NULL
#define         NULL                ((void *) 0)
#endif

#ifndef SUCCESS
#define         SUCCESS             1
#endif

#ifndef ERROR
#define         ERROR               0
#endif

#ifndef INVALID
#define         INVALID             0xFF
#endif

#ifndef ENABLE
#define         ENABLE                1
#endif
//
#ifndef DISABLE
#define         DISABLE               0
#endif

#ifndef WORD_SWAP
#define WORD_SWAP(X)    (((X << 8) | (X >> 8))&0xFFFF)
#endif

//=============================================================================
//dp数据点类型
//=============================================================================
#define         DP_TYPE_RAW                     0x00        //RAW型
#define         DP_TYPE_BOOL                    0x01        //布尔型
#define         DP_TYPE_VALUE                   0x02        //数值型
#define         DP_TYPE_STRING                  0x03        //字符串型
#define         DP_TYPE_ENUM                    0x04        //枚举型
#define         DP_TYPE_FAULT                   0x05        //故障型

//=============================================================================
//WIFI工作状态
//=============================================================================
#define         SMART_CONFIG_STATE              0x00
#define         AP_STATE                        0x01
#define         WIFI_NOT_CONNECTED              0x02
#define         WIFI_CONNECTED                  0x03
#define         WIFI_CONN_CLOUD                 0x04
#define         WIFI_LOW_POWER                  0x05
#define         SMART_AND_AP_STATE              0x06
#define         WIFI_SATE_UNKNOW                0xff

//=============================================================================
//wifi配网的方式
//=============================================================================
#define         SMART_CONFIG                    0x0  
#define         AP_CONFIG                       0x1   

//=============================================================================
//wifi复位状态
//=============================================================================
#define         RESET_WIFI_ERROR                0
#define         RESET_WIFI_SUCCESS              1

//=============================================================================
//设置wifi配置状态
//=============================================================================
#define         SET_WIFICONFIG_ERROR            0
#define         SET_WIFICONFIG_SUCCESS          1

//=============================================================================
//MCU固件升级状态
//=============================================================================
#define         FIRM_STATE_UN_SUPPORT           0x00                            //不支持 MCU 升级
#define         FIRM_STATE_WIFI_UN_READY        0x01                            //模块未就绪
#define         FIRM_STATE_GET_ERROR            0x02                            //云端升级信息查询失败
#define         FIRM_STATE_NO                   0x03                            //无需升级（云端无更新版本）
#define         FIRM_STATE_START                0x04                            //需升级，等待模块发起升级操作

//=============================================================================
//WIFI和mcu的工作方式
//=============================================================================
#define         UNION_WORK                      0x0                             //mcu模块与wifi配合处理
#define         WIFI_ALONE                      0x1                             //wifi模块自处理

//=============================================================================
//系统工作模式
//=============================================================================
#define         NORMAL_MODE                     0x00                            //正常工作状态
#define         FACTORY_MODE                    0x01                            //工厂模式
#define         UPDATE_MODE                     0x02                            //升级模式

//=============================================================================
//配网方式选择
//=============================================================================
#define         CONFIG_MODE_DEFAULT             0                            //默认配网方式
#define         CONFIG_MODE_LOWPOWER            1                            //低功耗配网方式
#define         CONFIG_MODE_SPECIAL             2                            //特殊配网方式

//=============================================================================
//设备能力是否开启选择选择
//=============================================================================
#define         ON                              1                              //设备能力开启
#define         OFF                             0                              //设备能力关闭

//=============================================================================
//一字节大小的buf最小为256
//=============================================================================
#define         BUF_SIZE                        50

//=============================================================================
//网关还是子设备的选择
//=============================================================================
#define         IS_GATEWAY                      1                               //是网关
#define         IS_SUBDEV                       0                               //是子设备


//=============================================================================
//网关本身子设备ID
//=============================================================================
#define         STR_GATEWAY_ITSELF_ID           ((unsigned char *)"0000")      //此子设备id表示网关本身


#include "protocol.h"
#include "system.h"
#include "mcu_api.h"


//=============================================================================
//下发命令
//=============================================================================
typedef struct {
    unsigned char dp_id;                    //dp序号
    unsigned char dp_type;                  //dp类型
} DOWNLOAD_CMD_S;

//子设备信息结构体
typedef struct {
    unsigned char if_subdev_net_in;         //子设备是否能入网  TRUE:允许 FALSE:不允许  必须在允许子设备入网的时候子设备才能入网
}SUBDEV_MANAGE_ST;

//#pragma anon_unions
//#pragma pack(1)
typedef union {
    struct{
        unsigned char   local_group            :1;      //本地群组
        unsigned char   local_scene            :1;      //本地场景
        unsigned char   gw_dev                 :1;      //网关有功能dp
        unsigned char   is_sigmesh             :1;      //sigmesh
        unsigned char   mcu_ota                :1;      //支持mcu升级
        unsigned char   group_sub              :1;      //群组控制指令带sub_id
        unsigned char   ble_uart_config        :1;      //蓝牙串口配网
        unsigned char   cancel_send_heartbeat  :1;      //取消心跳包
    };
    unsigned char whole;
}tSUB_ABILITY;

typedef struct {
    unsigned char  len;
    char           id[32]; //存放子设备id的内存，可根据最长子设备id长度情况定义大小
}tSUB_NODE;

#pragma pack()



#endif
