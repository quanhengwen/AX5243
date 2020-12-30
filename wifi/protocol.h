/**********************************Copyright (c)**********************************
**                       版权所有 (C), 2015-2020, 涂鸦科技
**
**                             http://www.tuya.com
**
*********************************************************************************/
/**
 * @file    protocol.h
 * @author  涂鸦综合协议开发组
 * @version v1.0.6
 * @date    2020.11.11
 * @brief                
 *                       *******非常重要，一定要看哦！！！********
 *          1. 用户在此文件中实现数据下发/上报功能
 *          2. DP的ID/TYPE及数据处理函数都需要用户按照实际定义实现
 *          3. 当开始某些宏定义后需要用户实现代码的函数内部有#err提示,完成函数后请删除该#err
 */


#ifndef __PROTOCOL_H_
#define __PROTOCOL_H_

/******************************************************************************
                            用户相关信息配置
******************************************************************************/
/******************************************************************************
                            1:修改产品信息                
******************************************************************************/
//pid信息，服务端自动插入
#define PRODUCT_KEY "q3xnn9yqt55ifaxm"    //开发平台创建产品后生成的16位字符产品唯一标识

#define MCU_VER "1.0.0"                                 //用户的软件版本,用于MCU固件升级,MCU升级版本需修改

//配网方式选择,默认为CONFIG_MODE_DEFAULT,只能三选一
#define CONFIG_MODE     CONFIG_MODE_DEFAULT             //默认配网方式
//#define CONFIG_MODE     CONFIG_MODE_LOWPOWER            //低功耗配网方式
//#define CONFIG_MODE     CONFIG_MODE_SPECIAL             //特殊配网方式

//smart和AP共存配网模式的特殊配置，如果不使用此宏定义，则在smart模式和AP模式之间切换
//#define CONFIG_MODE_CHOOSE        0         //同时打开AP和smart配网，不需要用户切换，网络状态为0x06
//#define CONFIG_MODE_CHOOSE        1         //只使用AP配网模式


/******************************************************************************
                          2:MCU是否需要支固件或者子设备升级

            **********************WARNING!!!**********************

如需要开启该功能,串口接收缓冲区会变大

mcu升级说明：
mcu升级类型分为四种
1. app 提醒升级：这个升级方式用户每次进入设备控制面板都会收到升级提醒的弹窗，
是否确认升级由用户自己在 APP 确认
2. app 静默升级：这个升级方式 app 不会有任何提醒弹窗，固件上电后一分钟内会去
自动去检测升级发现有高版本的升级包会自动开始拉取相关升级包，第一次上电后模块
会间隔 24 小时去云端检测一次是否有升级包配置。
3. app 强制升级: 这个升级方式 app 端会有升级提醒弹窗，如果用户不确认升级用户
就没法正常使用这个产品的控制面板。
4. app 检测升级:这个升级方式 app 端不会有任何升级提醒的弹窗，必须要用户在 app
端自己去点击相关固件版本检测，如果有高版本的固件配置才会显示升级提示信息。

WIFI 模块发送完所有的升级包，重新发送 01 命令字（3.2 查询产品信息）MCU 需要在
一分钟回复产品信息中的软件版本号带上升级后的 MCU 版本号，版本号需要和在涂鸦后台
配置升级的版本号保持一致。

如需要支持MCU固件升级或者是子设备升级,请开启该宏
******************************************************************************/
//#define         SUPPORT_MCU_FIRM_UPDATE                 //开启MCU固件升级功能(默认关闭)
#ifdef SUPPORT_MCU_FIRM_UPDATE
//固件升级包大小选择    0x00:256byte(默认)  0x01:512byte  0x02：1024byte
#define PACKAGE_SIZE                     0x00      //MCU固件升级包大小 256byte
//#define PACKAGE_SIZE                     0x01      //512byte
//#define PACKAGE_SIZE                     0x02      //1024byte
#endif
/******************************************************************************
                         3:定义收发缓存:
                    用户根据实际情况定义收发缓存的大小
******************************************************************************/
#ifndef SUPPORT_MCU_FIRM_UPDATE
#define WIFI_UART_RECV_BUF_LMT             128              //串口数据接收缓存区大小,如MCU的RAM不够,可缩小
#define WIFI_DATA_PROCESS_LMT          128              //串口数据处理缓存区大小,根据用户DP数据大小量定,建议大于24
#else
#define WIFI_UART_RECV_BUF_LMT             128              //串口数据接收缓存区大小,如MCU的RAM不够,可缩小

//当选择升级包单包大小的时候，选择单包256byte，512byte，1024byte，必须要扩大该buf的大小
//固件升级缓冲区,需大缓存
#define WIFI_DATA_PROCESS_LMT          300              //单包256byte
//#define WIFI_DATA_PROCESS_LMT          600              //单包512byte
//#define WIFI_DATA_PROCESS_LMT          1200             //单包1024byte
#endif

#define WIFIR_UART_SEND_BUF_LMT         128              //根据用户DP数据大小量定，用户可根据实际情况修改

/******************************************************************************
                        4:定义模块工作方式
模块自处理:
          wifi指示灯和wifi复位按钮接在wifi模块上(开启WIFI_CONTROL_SELF_MODE宏)
          并正确定义WF_STATE_KEY和WF_RESET_KEY
MCU自处理:
          wifi指示灯和wifi复位按钮接在MCU上(关闭WIFI_CONTROL_SELF_MODE宏)
          MCU在需要处理复位wifi的地方调用mcu_api.c文件内的mcu_reset_wifi()函数,并可调用mcu_get_reset_wifi_flag()函数返回复位wifi结果
          或调用设置wifi模式mcu_api.c文件内的mcu_set_wifi_mode(WIFI_CONFIG_E mode)函数,并可调用mcu_get_wifi_work_state()函数返回设置wifi结果
******************************************************************************/
//#define         WIFI_CONTROL_SELF_MODE                       //wifi自处理按键及LED指示灯;如为MCU外界按键/LED指示灯请关闭该宏
//例如：PORT为2，pin为3则代表选择GPIO C_3
#ifdef          WIFI_CONTROL_SELF_MODE                      //模块自处理
  #define     WF_LED_PORT            0                     //wifi状态指示灯的PORT（prot选择范围：0~3[依次代表A到D]），请根据实际GPIO管脚设置
  #define     WF_LED_PIN             0                     //wifi状态指示灯的PIN（prot选择范围：0~7），请根据实际GPIO管脚设置
  #define     WF_RESERT_KEY_PORT     0                     //重置按键的PORT（prot选择范围：0~3[依次代表A到D]），请根据实际GPIO管脚设置
  #define     WF_RESERT_KEY_PIN      0                     //重置按键的PIN（prot选择范围：0~7），请根据实际GPIO管脚设置
#endif

/******************************************************************************
                      MCU是否需要支持群组子设备加入和删除功能
如需要请开启该宏,并在Protocol.c文件内mcu_write_rtctime实现代码
mcu_write_rtctime内部有#err提示,完成函数后请删除该#err
mcu在wifi模块正确联网后可调用mcu_get_system_time()函数发起校时功能
******************************************************************************/
//#define         GROUP_SUBDEV_ENABLE                //开启群组子设备加入和删除功能

/******************************************************************************
                      MCU是否需要支持校时功能
如需要请开启该宏,并在Protocol.c文件内mcu_write_rtctime实现代码
mcu_write_rtctime内部有#err提示,完成函数后请删除该#err
mcu在wifi模块正确联网后可调用mcu_get_system_time()函数发起校时功能
******************************************************************************/
//#define         SUPPORT_MCU_RTC_CHECK                //开启校时功能

/******************************************************************************
                      MCU是否需要支持获取格林时间功能
如需要请开启该宏,并在Protocol.c文件内mcu_get_greentime实现代码
mcu_get_greentime内部有#err提示,完成函数后请删除该#err
mcu在wifi模块正确联网后可调用mcu_get_green_time()函数发起校时功能
******************************************************************************/
//#define         SUPPORT_GREEN_TIME                //开启格林时间功能

/******************************************************************************
                      MCU是否需要支持开启批量添加设备
如需要请开启该宏,并且mcu在需要wifi功能测试处调用mcu_api.c文件内batch_add_dev请求添加设备
并在protocol.c文件batch_add_dev_result函数内查看请求结果,内部有#err提示,完成函数后请删除该#err
可在protocol.c文件add_dev_result_get函数内查看最终添加设备结果,内部有#err提示,完成函数后请删除该#err
******************************************************************************/
//#define         BATCH_ADD_DEV_ENABLE              //开启批量添加设备

/******************************************************************************
                      MCU是否需要控制群组指令下发
如需要请开启该宏,并在protocol.c文件内ctrl_group_issued实现代码
ctrl_group_issued内部有#err提示,完成函数后请删除该#err
******************************************************************************/
//#define         CTRL_GROUP_DOWNLOAD_ENABLE             //开启控制群组指令下发功能

/******************************************************************************
                      MCU是否需要支持wifi功能测试
如需要请开启该宏,并且mcu在需要wifi功能测试处调用mcu_api.c文件内mcu_start_wifitest
并在protocol.c文件wifi_test_result函数内查看测试结果,
wifi_test_result内部有#err提示,完成函数后请删除该#err
******************************************************************************/
#define         WIFI_TEST_ENABLE                      //开启WIFI产测功能（扫描指定路由）

/******************************************************************************
                      MCU是否需要支持获取wifi状态
如需要请开启该宏,并且mcu在需要获取wifi状态处调用mcu_api.c文件内get_wifi_st
并在protocol.c文件wifi_status_result函数内查看结果,
wifi_status_result内部有#err提示,完成函数后请删除该#err
******************************************************************************/
//#define         GET_WIFI_STATUS_ENABLE                //开启获取wifi状态

/******************************************************************************
                      MCU是否需要支持恢复出厂设置
如需要请开启该宏,并且mcu在需要恢复出厂设置处调用mcu_api.c文件内reset_factory_setting
******************************************************************************/
//#define         RESET_FACTORY_SET_ENABLE              //开启恢复出厂设置

/******************************************************************************
                      MCU是否需要支持报告移除状态
如需要请开启该宏,
并在protocol.c文件inform_dev_del_status函数内查看结果,
inform_dev_del_status内部有#err提示,完成函数后请删除该#err
******************************************************************************/
//#define         INFORM_DEV_DEV_DEL_ENABLE              //开启报告移除状态

/******************************************************************************
                      MCU是否需要支持本地删除子设备
如需要请开启该宏,并且mcu在需要本地删除子设备处调用mcu_api.c文件内local_subdev_del_cmd
并在protocol.c文件local_del_subdev函数内查看结果,
local_del_subdev内部有#err提示,完成函数后请删除该#err
******************************************************************************/
//#define         LOCAL_SUBDEV_DEL_ENABLE                //开启本地删除子设备

/******************************************************************************
                      MCU是否需要支持本地允许/关闭添加子设备
如需要请开启该宏,并且mcu在需要本地允许/关闭添加子设备处调用mcu_api.c文件内local_add_subdev_limit
并在protocol.c文件local_subdev_limit函数内查看结果,
local_subdev_limit内部有#err提示,完成函数后请删除该#err
******************************************************************************/
//#define         LOCAL_ADD_SUBDEV_LIMIT_ENABLE          //开启本地允许/关闭添加子设备

/******************************************************************************
                      MCU是否需要支持获取模块内存
如需要请开启该宏,并且mcu在需要获取模块内存处调用mcu_api.c文件内get_module_remain_memory
并在protocol.c文件remain_memory_result函数内查看结果,
remain_memory_result内部有#err提示,完成函数后请删除该#err
******************************************************************************/
//#define         GET_MODULE_REMAIN_MEMORY_ENABLE        //开启获取模块内存

/******************************************************************************
                      MCU是否需要支持查询子设备列表
如需要请开启该宏,并且mcu在需要查询子设备列表处调用mcu_api.c文件内get_module_remain_memory
并在protocol.c文件remain_memory_result函数内查看结果,
remain_memory_result内部有#err提示,完成函数后请删除该#err
******************************************************************************/
//#define         QUR_SUBDEV_LIST_ENABLE                //开启查询子设备列表

/******************************************************************************
                      MCU是否需要控制群组指令下发（带sub_id）
如需要请开启该宏,并在protocol.c文件内ctrl_group_issued_sub_id实现代码
ctrl_group_issued_sub_id内部有#err提示,完成函数后请删除该#err
******************************************************************************/
//#define         CTRL_GROUP_DOWNLOAD_SUB_ID_ENABLE     //开启控制群组指令下发功能

/******************************************************************************
                      MCU是否需要支持串口配网（一体式）
如需要请开启该宏,并且mcu在需要串口配网（一体式）处调用mcu_api.c文件内uart_config_intrgrated
并在protocol.c文件uart_config_intrgrated_result函数内查看结果,
uart_config_intrgrated_result内部有#err提示,完成函数后请删除该#err
******************************************************************************/
//#define         UART_CONFIG_INTEGRATED_ENABLE         //开启串口配网（一体式）

/******************************************************************************
                      MCU是否需要支持串口透传配网(分布式)
如需要请开启该宏,并且mcu在需要串口透传配网(分布式)处调用mcu_api.c文件内的相关函数
并在protocol.c文件的相关函数内查看结果,
相关函数内部有#err提示,完成函数后请删除该#err
******************************************************************************/
//#define         UART_CONFIG_DISTRIBUTED_ENABLE        //开启串口透传配网(分布式)

/******************************************************************************
                      MCU是否需要支持查询dp状态
如需要请开启该宏,并在protocol.c文件内get_dp_state实现代码
get_dp_state内部有#err提示,完成函数后请删除该#err
******************************************************************************/
//#define         GET_DP_STATE_ENABLE                   //开启查询dp状态

/******************************************************************************
                      MCU是否需要支持更新子设备在线/离线状态
如需要请开启该宏,并且mcu在需要更新子设备在线/离线状态处调用mcu_api.c文件内updata_subden_online_state
并在protocol.c文件updata_subden_online_state_result函数内查看结果,
updata_subden_online_state_result内部有#err提示,完成函数后请删除该#err
******************************************************************************/
//#define         UPDATA_SUBDEV_ONLINE_STATE_ENABLE     //开启更新子设备在线/离线状态

/******************************************************************************
                      MCU是否需要支持获取模块的MAC地址
如需要请开启该宏,并且mcu在需要获取模块的MAC地址处调用mcu_api.c文件内get_module_mac
并在protocol.c文件get_module_mac_resultt函数内查看结果,
get_module_mac_result内部有#err提示,完成函数后请删除该#err
******************************************************************************/
//#define         GET_MODULE_MAC_ENABLE                 //开启获取模块的MAC地址

/******************************************************************************
                      MCU是否需要支持记录型状态实时上报（带时间）
如需要请开启该宏,并且mcu在需要记录型状态实时上报（带时间）处调用mcu_api.c文件内mcu_dp_XXX_update_record函数族，XXX需替换为dp类型
并在protocol.c文件record_state_upload_rt_result函数内查看结果,
record_state_upload_rt_result内部有#err提示,完成函数后请删除该#err
******************************************************************************/
//#define         RECORD_STATE_UPLOAD_RT_ENABLE         //开启记录型状态实时上报（带时间）

/******************************************************************************
                      MCU是否需要支持查询子设备绑定状态
如需要请开启该宏,并且mcu在需要查询子设备绑定状态处调用mcu_api.c文件内query_subdev_bind_state函数
并在protocol.c文件query_subdev_bind_state_result函数内查看结果,
query_subdev_bind_state_result内部有#err提示,完成函数后请删除该#err
******************************************************************************/
//#define         QUERY_SUBDEV_BIND_STATE_ENABLE         //开启查询子设备绑定状态

/******************************************************************************
                      MCU是否需要支持群组里的子设备
如需要请开启该宏,并且mcu在需要群组里的子设备处调用mcu_api.c文件内query_group_subdev函数
并在protocol.c文件query_group_subdev_result函数内查看结果,
query_group_subdev_result内部有#err提示,完成函数后请删除该#err
******************************************************************************/
//#define         QUERY_GROUP_SUBDEV_ENABLE             //开启查询群组里的子设备

/******************************************************************************
                      MCU是否需要支持上报群组本地改变的dp
如需要请开启该宏,并且mcu在需要上报群组本地改变的dp处调用mcu_api.c文件内upload_group_local_change_dp函数
并在protocol.c文件upload_group_local_change_dp_result函数内查看结果,
upload_group_local_change_dp_result内部有#err提示,完成函数后请删除该#err
******************************************************************************/
//#define         UPLOAD_GROUP_LOCAL_CHANGE_ENABLE      //开启上报群组本地改变的dp

/******************************************************************************
                      MCU是否需要支持安防传感相关功能
如需要请开启该宏,并且mcu在需要安防传感相关功能处调用mcu_api.c文件内相关函数
并在protocol.c文件中，在结果处理函数内查看结果,
这些函数内部有#err提示,完成函数后请删除该#err
******************************************************************************/
//#define         SECURITY_PROTECTION_ENABLE            //开启安防传感相关功能

#ifdef SECURITY_PROTECTION_ENABLE
/******************************************************************************
                      MCU是否需要支持安防网关安防报警信息显示
如需要请开启该宏,并且mcu在需要安防网关安防报警信息显示功能处调用mcu_api.c文件内相关函数
并在protocol.c文件中，在结果处理函数内查看结果,
这些函数内部有#err提示,完成函数后请删除该#err
******************************************************************************/
#define     SECURITY_PROTECTION_ALARM_DISPLAY_ENABLE        //开启安防网关安防报警信息显示功能
#endif

/******************************************************************************
                      MCU是否需要支持红外类相关功能
如需要请开启该宏,并且mcu在需要支持红外类相关功能处调用mcu_api.c文件内相关函数
并在protocol.c文件中，在结果处理函数内查看结果,
这些函数内部有#err提示,完成函数后请删除该#err
******************************************************************************/
//#define         IR_CTRL_ENABLE                      //开启支持红外类相关功能

/******************************************************************************
                      是否开启天气功能
如需要请开启该宏,并在protocol.c文件内weather_open_return_handle与weather_data_user_handle两个用户处理函数中实现显示等代码
此两函数内#err提示,完成函数后请删除该#err
开启天气功能，串口数据缓存区的大小要开大一些
******************************************************************************/
//#define         WEATHER_ENABLE                      //打开天气功能
#ifdef          WEATHER_ENABLE
/*  在protocol.c文件中weather_choose数组中可调整，然后将打开服务的类型数目写到此宏定义  */
#define         WEATHER_CHOOSE_CNT              4   //选择的需要天气服务类型的数目
/*  在打开天气服务时，可以设置此宏定义选择天气预报的天数，1表示当天天气(不需要预报可设置为1)，最多为7天(不可以设置成0或大于7)  */
#define         WEATHER_FORECAST_DAYS_NUM       1   //设置天气预报的天数
/*  天气更新时间间隔    0：表示默认值60min   0xFF：表示24h更新一次  */
#define         WEATHER_UPDATE_TIME_LAG         60   //天气更新时间间隔(单位:min)
#endif

/******************************************************************************
                      MCU是否需要支持带时区格林时间功能
如需要请开启该宏,并在Protocol.c文件内 get_green_time_with_zone_result 实现代码
get_green_time_with_zone_result 内部有#err提示,完成函数后请删除该#err
mcu在wifi模块正确联网后可调用 get_green_time_with_zone() 函数发起校时功能
******************************************************************************/
//#define         GREEN_TIME_WITH_ZONE_ENABLE         //开启带时区格林时间功能

/******************************************************************************
                      MCU是否需要支持心跳查询管理功能
如需要请开启该宏,并在Protocol.c文件内 get_green_time_with_zone_result 实现代码
get_green_time_with_zone_result 内部有#err提示,完成函数后请删除该#err
mcu在wifi模块正确联网后可调用 get_green_time_with_zone() 函数发起校时功能
******************************************************************************/
//#define         HEART_QUERY_MANAGE_ENABLE         //开启心跳查询管理功能



/******************************************************************************
                        1:网关的dp数据点序列号重新定义
          **此为自动生成代码,如在开发平台有相关修改请重新下载MCU_SDK**         
******************************************************************************/
//故障状态(只上报)
//备注:
#define DPID_FAIL_STATE 101
//故障设备ID(只上报)
//备注:
#define DPID_DEVICE_ID 102
//阀门状态(可下发可上报)
//备注:
#define DPID_VALVE_STATE 103




/**
 * @brief  串口发送数据
 * @param[in] {value} 串口要发送的1字节数据
 * @return Null
 */
void uart_transmit_output(unsigned char value);

/**
 * @brief  系统所有dp点信息上传,实现APP和muc数据同步
 * @param  Null
 * @return Null
 * @note   此函数SDK内部需调用，MCU必须实现该函数内数据上报功能，包括只上报和可上报可下发型数据
 */
void all_data_update(void);

/**
 * @brief  dp下发处理函数
 * @param[in] {dpid} dpid 序号
 * @param[in] {value} dp数据缓冲区地址
 * @param[in] {length} dp数据长度
 * @return dp处理结果
 * -           0(ERROR): 失败
 * -           1(SUCCESS): 成功
 * @note   该函数用户不能修改
 */
unsigned char dp_download_handle(unsigned char dpid,const unsigned char value[], unsigned short length,unsigned char* sub_id,unsigned char sub_id_len);

/**
 * @brief  获取所有dp命令总和
 * @param[in] Null
 * @return 下发命令总和
 * @note   该函数用户不能修改
 */
unsigned char get_download_cmd_total(void);


/**
 * @brief  wifi模块是否接收子设备入网请求结果通知（子设备是否实
           际入网成功需要查看ADD_DEV_RESULT_CMD命令字相关的命令）
 * @param[in] {result} 模块是否接收子设备入网请求结果;0:接收请求/1:拒绝请求
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void subdevice_add_result(unsigned char result);

/**
 * @brief  wifi模块发送关闭入网指令给网关,此函数内获取需要删除
           的子设备id和子设备key，用户需要根据这两条信息自行删除子设备
 * @param[in] {data_buf} 接收到的data部分的首地址
 * @param[in] {data_len} 接收到的data部分的长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void subdevice_delete(unsigned char* data_buf,unsigned short data_len);

/**
 * @brief  wifi模块WIFI 模组定时（1-3 分钟）检测子设备在线状态
 * @param[in] {data_buf} 接收到的data部分的首地址
 * @param[in] {data_len} 接收到的data部分的长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void heart_beat_check(unsigned char* data_buf,unsigned short data_len);

#ifdef GROUP_SUBDEV_ENABLE
/**
 * @brief  群组子设备加入
 * @param[in] {data_buf} 接收到的data部分的首地址
 * @param[in] {data_len} 接收到的data部分的长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void group_subdev_add(unsigned char *data_buf, unsigned short data_len);

/**
 * @brief  群组子设备删除
 * @param[in] {data_buf} 接收到的data部分的首地址
 * @param[in] {data_len} 接收到的data部分的长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void group_subdev_del(unsigned char *data_buf, unsigned short data_len);
#endif


#ifdef SUPPORT_GREEN_TIME
/**
 * @brief  获取到的格林时间
 * @param[in] {time} 获取到的格林时间数据
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_get_greentime(unsigned char time[]);
#endif

#ifdef SUPPORT_MCU_RTC_CHECK
/**
 * @brief  MCU校对本地RTC时钟
 * @param[in] {time} 获取到的本地时间数据
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_write_rtctime(unsigned char time[]);
#endif

#ifdef BATCH_ADD_DEV_ENABLE
/**
 * @brief  批量添加同一个pid的多个子设备请求结果通知
 * @param[in] {result} 模块是否接收子设备添加请求结果;0:接收请求/1:拒绝请求
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void batch_add_dev_result(unsigned char result);

/**
 * @brief  批量添加设备添加结果处理
 * @param[in] {cids} 子设备集合
 * @param[in] {rets} 0成功，非0失败
 * @param[in] {keys} 秘钥，仅单点设备使用，其他为NULL
 * @param[in] {num} 子设备的数量
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void add_dev_result_get(unsigned char* data_buf,unsigned short data_len);
#endif

#ifdef CTRL_GROUP_DOWNLOAD_ENABLE
/**
 * @brief  控制群组指令下发
 * @param[in] {value} 数据缓存
 * @param[in] {group_id_buf} 群组id
 * @param[in] {group_id_len} 群组id长度
 * @return 成功/失败
 * @note   MCU需要自行实现该功能
 */
unsigned char ctrl_group_issued(const unsigned char value[],const unsigned char group_id_buf[],unsigned short group_id_len);
#endif

#ifdef WIFI_TEST_ENABLE
/**
 * @brief  wifi功能测试反馈
 * @param[in] {result} wifi功能测试结果;0:失败/1:成功
 * @param[in] {rssi} 测试成功表示wifi信号强度/测试失败表示错误类型
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void wifi_test_result(unsigned char result,unsigned char rssi);
#endif

#ifdef GET_WIFI_STATUS_ENABLE
/**
 * @brief  获取 WIFI 状态结果
 * @param[in] {result} 指示 WIFI 工作状态
 * @ref         0x00: wifi状态 1 smartconfig 配置状态
 * @ref         0x01: wifi状态 2 AP 配置状态
 * @ref         0x02: wifi状态 3 WIFI 已配置但未连上路由器
 * @ref         0x03: wifi状态 4 WIFI 已配置且连上路由器
 * @ref         0x04: wifi状态 5 已连上路由器且连接到云端
 * @ref         0x05: wifi状态 6 WIFI 设备处于低功耗模式
 * @ref         0x06: wifi状态 7 Smartconfig&AP共存状态
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void wifi_status_result(unsigned char result);
#endif

#ifdef INFORM_DEV_DEV_DEL_ENABLE
/**
 * @brief  1 网关收到移除或者恢复出厂命令时，会向 MCU 报告状态。
           2 如果仅收到移除指令，网关只会移除配网，并不会删除子设备信息，
             下次联网时，子设备信息仍会在 app 上显示。
           3 如果收到恢复出厂指令，网关会移除配网并且清除所有子设备信息。
 * @param[in] {result} 移除方式
 * @ref           0x00: 本地恢复出厂
 * @ref           0x01: 远程移除
 * @ref           0x02: 本地移除
 * @ref           0x03: 远程恢复出厂
 * @ref           0x04: 清除数据，但是网关不离网
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void inform_dev_del_status(unsigned char result);
#endif

#ifdef LOCAL_SUBDEV_DEL_ENABLE
/**
 * @brief  本地删除子设备结果
 * @param[in] {result} 本地子设备删除结果结果;0:成功/1:失败
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void local_del_subdev(unsigned char result);
#endif

#ifdef LOCAL_ADD_SUBDEV_LIMIT_ENABLE
/**
 * @brief  本地允许/关闭添加子设备结果通知
 * @param[in] {result} 
 * @ref           0: 本地允许/关闭添加子设备成功
 * @ref           1: 本地允许/关闭添加子设备失败
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void local_subdev_limit(unsigned char result);
#endif

#ifdef GET_MODULE_REMAIN_MEMORY_ENABLE
/**
 * @brief  获取模块内存
 * @param[in] {module_memory} 获取模块内存的大小
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void remain_memory_result(unsigned int module_memory);
#endif

#ifdef QUR_SUBDEV_LIST_ENABLE
/**
 * @brief  子设备列表
 * @param[in] {subdev_list_buf} 存放子设备的buf
 * @param[in] {buf_len} 子设备buf的长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void local_subdev_list(unsigned char *subdev_list_buf,unsigned short buf_len);
#endif

#ifdef SUPPORT_MCU_FIRM_UPDATE
/**
 * @brief  网关本身MCU升级包大小选择
 * @param[in] {package_sz} 升级包大小
 * @ref           0x00: 256byte (默认)
 * @ref           0x01: 512byte
 * @ref           0x02: 1024byte
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void upgrade_package_choose(unsigned char package_sz);

/**
 * @brief  网关本身MCU升级包传输
 * @param[in] {value} 固件数据缓冲区
 * @param[in] {position} 当前数据包在于固件位置
 * @param[in] {length} 当前固件包长度(固件包长度为0时,表示固件包发送完成)
 * @return 成功/失败
 * @note   MCU需要自行实现该功能
 */
unsigned char mcu_firm_update_handle(const unsigned char value[],unsigned long position,unsigned short length);

/**
 * @brief  子设备MCU升级包大小选择
 * @param[in] {package_sz} 升级包大小
 * @ref           0x00: 256byte (默认)
 * @ref           0x01: 512byte
 * @ref           0x02: 1024byte
 * @param[in] {sub_dev_id} 子设备id
 * @param[in] {sub_dev_len} 子设备长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void subdev_upgrade_package_choose(unsigned char package_sz,unsigned char*sub_dev_id,unsigned char sub_dev_len);

/**
 * @brief  子设备MCU升级包大小选择
 * @param[in] {sub_id_buf} 子设备id
 * @param[in] {value} 固件数据缓冲区
 * @param[in] {position} 当前数据包在于固件位置
 * @param[in] {length} 当前固件包长度(固件包长度为0时,表示固件包发送完成)
 * @return 成功/失败
 * @note   MCU需要自行实现该功能
 */
unsigned char subdev_firm_update_handle(unsigned char *sub_id_buf,const unsigned char value[],unsigned long position,unsigned short length);

/**
 * @brief  wifi模块查询子设备版本号
 * @param[in] {data_buf} 接收到的data部分的首地址
 * @param[in] {data_len} 接收到的data部分的长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void qur_subdev_ver_get(unsigned char* data_buf,unsigned short data_len);
#endif

#ifdef CTRL_GROUP_DOWNLOAD_SUB_ID_ENABLE
/**
 * @brief  控制群组指令下发(带sub_id)
 * @param[in] {value} 数据缓存
 * @param[in] {group_id_buf} 群组id
 * @param[in] {group_id_len} 群组id长度
 * @param[in] {sub_id_buf} 子设备id
 * @param[in] {sub_id_len} 子设备id长度
 * @return 成功/失败
 * @note   MCU需要自行实现该功能
 */
unsigned char ctrl_group_issued_sub_id(const unsigned char value[], const unsigned char group_id_buf[], unsigned short group_id_len, \
                                                                    const unsigned char sub_id_buf[], unsigned short sub_id_len);
#endif

#ifdef UART_CONFIG_INTEGRATED_ENABLE
/**
 * @brief  串口配网（一体式）结果处理
 * @param[in] {result} 模块返回结果
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void uart_config_intrgrated_result(unsigned char result);
#endif

#ifdef UART_CONFIG_DISTRIBUTED_ENABLE        //开启串口透传配网(分布式)
/**
 * @brief  WIFI发送广播包( 串口透传配网(分布式) )数据处理
 * @param[in] {p_data} 广播包数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void send_broad_packet(const unsigned char p_data[], unsigned short data_len);

/**
 * @brief  WIFI上报配网信息( 串口透传配网(分布式) )
 * @param[in] {p_data} 加密数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void upload_config_infor(const unsigned char p_data[], unsigned short data_len);

/**
 * @brief  wifi模块主动断开连接( 串口透传配网(分布式) )
 * @param  Null
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void wifi_disconnect(void);
#endif

#ifdef GET_DP_STATE_ENABLE
/**
 * @brief  查询dp状态
 * @param[in] {p_data} 数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void get_dp_state(const unsigned char p_data[], unsigned short data_len);
#endif

#ifdef UPDATA_SUBDEV_ONLINE_STATE_ENABLE
/**
 * @brief  更新子设备在线/离线状态结果处理
 * @param[in] {result} 模块返回结果
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void updata_subden_online_state_result(unsigned char result);
#endif

#ifdef GET_MODULE_MAC_ENABLE
/**
 * @brief  获取模块的MAC地址结果处理
 * @param[in] {p_data} 数据
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void get_module_mac_result(const unsigned char p_data[]);
#endif

#ifdef RECORD_STATE_UPLOAD_RT_ENABLE
/**
 * @brief  记录型状态实时上报（带时间）结果处理
 * @param[in] {result} 模块返回结果
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void record_state_upload_rt_result(unsigned char result);
#endif

#ifdef QUERY_SUBDEV_BIND_STATE_ENABLE
/**
 * @brief  查询子设备绑定状态结果
 * @param[in] {p_data} 数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void query_subdev_bind_state_result(const unsigned char p_data[], unsigned short data_len);
#endif

#ifdef QUERY_GROUP_SUBDEV_ENABLE
/**
 * @brief  查询群组里的子设备结果
 * @param[in] {p_data} 数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void query_group_subdev_result(const unsigned char p_data[], unsigned short data_len);
#endif

#ifdef UPLOAD_GROUP_LOCAL_CHANGE_ENABLE
/**
 * @brief  上报群组本地改变的dp结果
 * @param[in] {result} 模块返回结果
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void upload_group_local_change_dp_result(unsigned char result);
#endif

#ifdef IR_CTRL_ENABLE
/**
 * @brief  红外控制码发送数据处理
 * @param[in] {p_data} 数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void ir_ctrl_cmd_send(const unsigned char p_data[], unsigned short data_len);

/**
 * @brief  红外控制码学习
 * @param[in] {p_data} 数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void ir_ctrl_cmd_learn(const unsigned char p_data[], unsigned short data_len);

/**
 * @brief  红外控制码取消学习
 * @param  Null
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void ir_ctrl_cmd_cancel_learn(void);
#endif

#ifdef WEATHER_ENABLE
/**
* @brief  mcu打开天气服务
 * @param  Null
 * @return Null
 */
void mcu_open_weather(void);

/**
 * @brief  打开天气功能返回用户自处理函数
 * @param[in] {res} 打开天气功能返回结果
 * @ref       0: 失败
 * @ref       1: 成功
 * @param[in] {err} 错误码
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void weather_open_return_handle(unsigned char res, unsigned char err);

/**
 * @brief  天气数据用户自处理函数
 * @param[in] {name} 参数名
 * @param[in] {type} 参数类型
 * @ref       0: int 型
 * @ref       1: string 型
 * @param[in] {data} 参数值的地址
 * @param[in] {day} 哪一天的天气  0:表示当天 取值范围: 0~6
 * @ref       0: 今天
 * @ref       1: 明天
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void weather_data_user_handle(char *name, unsigned char type, const unsigned char *data, char day);

/**
* @brief  mcu主动获取天气服务
 * @param  Null
 * @return Null
 */
void mcu_get_weather(void);

/**
 * @brief  mcu主动获取天气服务结果
 * @param[in] {result} 获取天气返回结果
 * @ref       0: 成功
 * @ref       1: 失败
 * @param[in] {err} 错误码
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_get_weather_result(unsigned char result);
#endif

#ifdef GREEN_TIME_WITH_ZONE_ENABLE
/**
 * @brief  获取带时区系统（格林）时间数据结果
 * @param[in] {p_data} 数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void get_green_time_with_zone_result(const unsigned char p_data[], unsigned short data_len);
#endif

#ifdef SECURITY_PROTECTION_ENABLE
/**
 * @brief  安防信息相关结果
 * @param[in] {p_data} 数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void security_protect_infor_result(const unsigned char p_data[], unsigned short data_len);

/**
 * @brief  报警相关结果
 * @param[in] {p_data} 数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void alarm_infor_result(const unsigned char p_data[], unsigned short data_len);
#endif


#endif

