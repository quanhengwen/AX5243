/**********************************Copyright (c)**********************************
**                       版权所有 (C), 2015-2020, 涂鸦科技
**
**                             http://www.tuya.com
**
*********************************************************************************/
/**
 * @file    system.h
 * @author  涂鸦综合协议开发组
 * @version v1.0.6
 * @date    2020.11.11
 * @brief   串口数据处理，用户无需关心该文件实现内容
 */
  

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

#define SYSTEM_EXTERN   extern

//=============================================================================
//帧的字节顺序
//=============================================================================
#define         HEAD_FIRST                      0
#define         HEAD_SECOND                     1
#define         PROTOCOL_VERSION                2
#define         FRAME_TYPE                      3
#define         LENGTH_HIGH                     4
#define         LENGTH_LOW                      5
#define         DATA_START                      6

//=============================================================================
//数据帧类型
//=============================================================================
#define         PRODUCT_INFO_CMD                0x01                            //产品信息
#define         WORK_MODE_CMD                   0x02                            //查询MCU 设定的模块工作模式  
#define         WIFI_STATE_CMD                  0x03                            //wifi工作状态	
#define         WIFI_RESET_CMD                  0x04                            //重置wifi
#define         WIFI_MODE_CMD                   0x05                            //选择smartconfig/AP模式	
#define         PERMIT_SUBDEVICE_NETIN_CMD      0x06                            //允许子设备入网
#define         CLOSE_SUBDEVICE_NETIN_CMD       0x07                            //关闭子设备入网
#define         SUBDEVICE_ADD_CMD               0x08                            //子设备添加
#define         SUBDEVICE_DELETTE_CMD           0x09                            //子设备删除
#define         HEART_CHECK_CMD                 0x0a                            //心跳检测
#define         STATE_QUERY_CMD                 0x0b                            //状态查询（用于同步设子设备状态）
#define         DATA_ISSUED_CMD                 0x0c                            //命令下发
#define         STATE_UPLOAD_CMD                0x0d                            //状态上报
#define         GROUP_SUBDEV_ADD_CMD            0x0e                            //群组子设备加入
#define         GROUP_SUBDEV_DEL_CMD            0x0f                            //群组子设备删除
#define         GET_ONLINE_TIME_CMD             0x10                            //获取系统时间(格林威治时间)
#define         GET_LOCAL_TIME_CMD              0x11                            //获取本地时间
#define         BATCH_ADD_DEV_CMD               0x12                            //批量添加设备
#define         ADD_DEV_RESULT_CMD              0x13                            //返回添加设备结果
#define         CTRL_GROUP_DOWNLOAD_CMD         0x14                            //控制群组指令下发
#define         WIFI_TEST_CMD                   0x15                            //wifi功能测试
#define         GET_WIFI_STATUS_CMD             0x16                            //获取wifi状态
#define         FACTORY_SET_CMD                 0x17                            //恢复出厂设置
#define         INFORM_DEV_DEV_DEL_CMD          0x18                            //报告移除状态
#define         LOCAL_SUBDEV_DEL_CMD            0x19                            //本地删除子设备
#define         LOCAL_ADD_SUBDEV_LIMIT_CMD      0x1a                            //本地允许/关闭添加子设备
#define         GET_MODULE_REMAIN_MEMORY_CMD    0x1b                            //获取模块内存
#define         QUR_SUBDEV_LIST_CMD             0x1c                            //查询子设备列表
#define         UPDATE_START_CMD                0x1d                            //网关启动升级
#define         UPDATE_TRANS_CMD                0x1e                            //网关升级传输中
#define         SUBDEV_START_UPGRADE_CMD        0x1f                            //子设备启动升级
#define         SUBDEV_TRANS_CMD                0x20                            //子设备升级包传输
#define         QUR_SUBDEV_VER_CMD              0x21                            //查询子设备版本号
#define         CTRL_GROUP_DOWNLOAD_SUB_CMD     0x22                            //控制群组指令下发(带sub_id)
#define         UART_CONFIG_CMD                 0x23                            //串口配网（一体式）
#define         SEND_BROAD_PACKET_CMD           0x24                            //WIFI发送广播包( 串口透传配网(分布式) )
#define         SEND_CONFIG_INFOR_CMD           0x25                            //MCU发送配网信息( 串口透传配网(分布式) )
#define         UPLOAD_CONFIG_INFOR_CMD         0x26                            //WIFI上报配网信息( 串口透传配网(分布式) )
#define         MCU_CONNECT_STATE_CMD           0x27                            //MCU连接状态( 串口透传配网(分布式) )
#define         WIFI_DISCONNECT_CMD             0x28                            //wifi模块主动断开连接( 串口透传配网(分布式) )
#define         GET_DP_STATE_CMD                0x29                            //查询dp状态
#define         UPDATA_SUBDEV_ONLINE_STATE_CMD  0x2a                            //更新子设备在线/离线状态
#define         GET_MODULE_MAC_CMD              0x2b                            //获取模块的MAC地址
#define         RECORD_STATE_UPLOAD_RT_CMD      0x2c                            //记录型状态实时上报（带时间）
#define         QUERY_SUBDEV_BIND_STATE_CMD     0x2d                            //查询子设备绑定状态
#define         QUERY_GROUP_SUBDEV_CMD          0x2e                            //查询群组里的子设备
#define         UPLOAD_GROUP_LOCAL_CHANGE_CMD   0x2f                            //上报群组本地改变的dp
#define         IR_CTRL_CMD_SEND_CMD            0x30                            //红外类控制码发送
#define         IR_CTRL_CMD_LEARN_CMD           0x31                            //红外类控制码学习
#define         IR_CTRL_CMD_CANCEL_LEARN_CMD    0x32                            //红外类控制码取消学习
#define         EXPAND_FUNC_CMD                 0x33                            //拓展功能
#define         SECURITY_PROTECT_INFOR_CMD      0xc0                            //安防信息
#define         SECURITY_PROTECT_ALARM_CMD      0xc1                            //安防报警


//=============================================================================
//子命令
//=============================================================================
#ifdef EXPAND_FUNC_CMD //拓展功能
#define OPEN_WEATHER_SUBCMD                         0x00            //打开天气
#define WEATHER_DATA_SUBCMD                         0x01            //天气数据下发
#define GET_WEATHER_SUBCMD                          0x02            //MCU主动获取天气数据
#define GET_GREEN_TIME_WITH_ZONE_SUBCMD             0x03            //带时区系统（格林）时间数据下发
#define HEART_QUERY_MANAGE_SUBCMD                   0x04            //心跳查询管理
#endif

#ifdef SECURITY_PROTECT_INFOR_CMD //安防信息
#define DEFENCE_MODE_SET_SUBCMD                     0x00            //当前布防模式设置
#define SECURITY_PROTECT_INFOR_GET_SUBCMD           0x01            //当前安防信息获取
#define SECURITY_PROTECT_INFOR_SYN_SUBCMD           0x02            //安防信息同步
#define DEV_SECURITY_PROTECT_EVENT_SYN_SUBCMD       0x03            //设备安防事件同步
#endif

#ifdef SECURITY_PROTECT_ALARM_CMD //安防报警
#define ALARM_STATE_SET_SUBCMD                      0x00            //报警状态设置
#define CANCEL_ALARM_STATE_SET_SUBCMD               0x01            //取消报警状态同步
#define DEV_ALARM_INFOR_SYN_SUBCMD                  0x02            //设备报警信息同步
#define DEV_ALARM_DELAY_STATE_SUBCMD                0x03            //设备报警延时状态同步
#define NEW_DEV_ALARM_INFOR_DISPLAY_SYN_SUBCMD      0x04            //新设备报警信息显示同步
#define NEW_DEV_ALARM_DELAY_STATE_SUBCMD            0x05            //新设备报警状态同步
#endif


//=============================================================================
#define MCU_RX_VER              0x00                                            //接收的协议版本号
#define MCU_TX_VER              0x00                                            //发送的协议版本号
#define PROTOCOL_HEAD           0x07                                            //固定协议头长度
#define FRAME_FIRST             0x55
#define FRAME_SECOND            0xaa
//============================================================================= 
SYSTEM_EXTERN volatile unsigned char wifi_data_process_buf[PROTOCOL_HEAD + WIFI_DATA_PROCESS_LMT];      //串口数据处理缓存
SYSTEM_EXTERN volatile unsigned char wifi_uart_rx_buf[PROTOCOL_HEAD + WIFI_UART_RECV_BUF_LMT];          //串口接收缓存
SYSTEM_EXTERN volatile unsigned char wifi_uart_tx_buf[PROTOCOL_HEAD + WIFIR_UART_SEND_BUF_LMT];         //串口发送缓存

SYSTEM_EXTERN volatile unsigned char *queue_in;
SYSTEM_EXTERN volatile unsigned char *queue_out;

SYSTEM_EXTERN volatile unsigned char stop_update_flag;                                                 //停止一切数据上报

SYSTEM_EXTERN volatile unsigned char stop_subdev_update_flag;                                          //停止正在升级的子设备数据上报

#ifndef WIFI_CONTROL_SELF_MODE
SYSTEM_EXTERN volatile unsigned char reset_wifi_flag;                                                  //重置wifi标志(TRUE:成功/FALSE:失败)
SYSTEM_EXTERN volatile unsigned char set_wifimode_flag;                                                //设置WIFI工作模式标志(TRUE:成功/FALSE:失败)
SYSTEM_EXTERN volatile unsigned char wifi_work_state;                                                  //wifi模块当前工作状态
#endif

/**
 * @brief  写wifi_uart字节
 * @param[in] {dest} 缓存区地址偏移
 * @param[in] {byte} 写入字节值
 * @return 写入完成后的总长度
 */
unsigned short set_wifi_uart_byte(unsigned short dest, unsigned char byte);

/**
 * @brief  写wifi_uart_buffer
 * @param[in] {dest} 缓存区地址偏移
 * @param[in] {src} 源地址（需要发送的数据）
 * @param[in] {len} 需要发送的数据长度
 * @return 写入完成后的总长度
 */
unsigned short set_wifi_uart_buffer(unsigned short dest, const unsigned char *src, unsigned short len);

/**
 * @brief  计算校验和
 * @param[in] {pack} 数据源指针
 * @param[in] {pack_len} 计算校验和长度
 * @return 校验和
 */
unsigned char get_check_sum(unsigned char *pack, unsigned short pack_len);

/**
 * @brief  向wifi串口发送一帧数据
 * @param[in] {fr_type} 帧类型
 * @param[in] {fr_ver} 帧版本
 * @param[in] {len} 数据长度
 * @return Null
 */
void wifi_uart_write_frame(unsigned char fr_type, unsigned char fr_ver, unsigned short len);

/**
 * @brief  获取制定DPID在数组中的序号
 * @param[in] {dpid} dpid
 * @return dp序号
 */
unsigned char get_dowmload_dpid_index(unsigned char dpid);

/**
 * @brief  数据帧处理
 * @param[in] {offset} 数据起始位
 * @return Null
 */
void data_handle(unsigned short offset);

/**
 * @brief  判断串口接收缓存中是否有数据
 * @param  Null
 * @return 是否有数据  0:无/1:有
 */
unsigned char get_queue_total_data(void);

/**
 * @brief  读取队列1字节数据
 * @param  Null
 * @return Read the data
 */
unsigned char Queue_Read_Byte(void);

#endif
  
  
