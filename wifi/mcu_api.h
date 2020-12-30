/**********************************Copyright (c)**********************************
**                       版权所有 (C), 2015-2020, 涂鸦科技
**
**                             http://www.tuya.com
**
*********************************************************************************/
/**
 * @file    mcu_api.h
 * @author  涂鸦综合协议开发组
 * @version v1.0.6
 * @date    2020.11.11
 * @brief   用户需要主动调用的函数都在该文件内
 */
 
 
#ifndef __MCU_API_H_
#define __MCU_API_H_

#ifdef MCU_API_GLOBAL
  #define MCU_API_EXTERN
#else
  #define MCU_API_EXTERN   extern
#endif
  
#include "protocol.h"

/**
 * @brief  hex转bcd
 * @param[in] {Value_H} 高字节
 * @param[in] {Value_L} 低字节
 * @return 转换完成后数据
 */
unsigned char hex_to_bcd(unsigned char Value_H,unsigned char Value_L);
/**
 * @brief  求字符串长度
 * @param[in] {str} 字符串地址
 * @return 数据长度
 */
unsigned long my_strlen(unsigned char *str);

/**
 * @brief  把src所指内存区域的前count个字节设置成字符c
 * @param[out] {src} 待设置的内存首地址
 * @param[in] {ch} 设置的字符
 * @param[in] {count} 设置的内存长度
 * @return 待设置的内存首地址
 */
void *my_memset(void *src,unsigned char ch,unsigned short count);

/**
 * @brief  内存拷贝
 * @param[out] {dest} 目标地址
 * @param[in] {src} 源地址
 * @param[in] {count} 拷贝数据个数
 * @return 数据处理完后的源地址
 */
void *my_memcpy(void *dest, const void *src, unsigned short count);

/**
 * @brief  字符串拷贝
 * @param[in] {dest} 目标地址
 * @param[in] {src} 源地址
 * @return 数据处理完后的源地址
 */
char *my_strcpy(char *dest, const char *src);

/**
 * @brief  字符串比较
 * @param[in] {s1} 字符串 1
 * @param[in] {s2} 字符串 2
 * @return 大小比较值
 * -         0:s1=s2
 * -         <0:s1<s2
 * -         >0:s1>s2
 */
int my_strcmp(char *s1 , char *s2);

/**
 * @brief  将int类型拆分四个字节
 * @param[in] {number} 4字节原数据
 * @param[out] {value} 处理完成后4字节数据
 * @return Null
 */
void int_to_byte(unsigned long number,unsigned char value[4]);

/**
 * @brief  将4字节合并为1个32bit变量
 * @param[in] {value} 4字节数组
 * @return 合并完成后的32bit变量
 */
unsigned long byte_to_int(const unsigned char value[4]);

/**
 * @brief  raw型dp数据上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值指针
 * @param[in] {len} 数据长度
 * @param[in] {sub_id_buf} 存放子设备id的首地址
 * @param[in] {sub_id_len} 子设备id长度
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_raw_update(unsigned char dpid,const unsigned char value[],unsigned short len,unsigned char *sub_id_buf,unsigned char sub_id_len);

/**
 * @brief  bool型dp数据上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值
 * @param[in] {sub_id_buf} 存放子设备id的首地址
 * @param[in] {sub_id_len} 子设备id长度
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_bool_update(unsigned char dpid,unsigned char value,unsigned char *sub_id_buf,unsigned char sub_id_len);

/**
 * @brief  value型dp数据上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值
 * @param[in] {sub_id_buf} 存放子设备id的首地址
 * @param[in] {sub_id_len} 子设备id长度
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_value_update(unsigned char dpid,unsigned long value,unsigned char *sub_id_buf,unsigned char sub_id_len);

/**
 * @brief  string型dp数据上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值指针
 * @param[in] {len} 数据长度
 * @param[in] {sub_id_buf} 存放子设备id的首地址
 * @param[in] {sub_id_len} 子设备id长度
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_string_update(unsigned char dpid,const unsigned char value[],unsigned short len,unsigned char *sub_id_buf,unsigned char sub_id_len);

/**
 * @brief  enum型dp数据上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值
 * @param[in] {sub_id_buf} 存放子设备id的首地址
 * @param[in] {sub_id_len} 子设备id长度
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_enum_update(unsigned char dpid,unsigned char value,unsigned char *sub_id_buf,unsigned char sub_id_len);

/**
 * @brief  fault型dp数据上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值
 * @param[in] {sub_id_buf} 存放子设备id的首地址
 * @param[in] {sub_id_len} 子设备id长度
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_fault_update(unsigned char dpid,unsigned long value,unsigned char *sub_id_buf,unsigned char sub_id_len);

/**
 * @brief  mcu获取bool型下发dp值
 * @param[in] {value} dp数据缓冲区地址
 * @param[in] {len} dp数据长度
 * @return 当前dp值
 * @note   Null
 */
unsigned char mcu_get_dp_download_bool(const unsigned char value[],unsigned short len);

/**
 * @brief  mcu获取enum型下发dp值
 * @param[in] {value} dp数据缓冲区地址
 * @param[in] {len} dp数据长度
 * @return 当前dp值
 * @note   Null
 */
unsigned char mcu_get_dp_download_enum(const unsigned char value[],unsigned short len);

/**
 * @brief  mcu获取value型下发dp值
 * @param[in] {value} dp数据缓冲区地址
 * @param[in] {len} dp数据长度
 * @return 当前dp值
 * @note   Null
 */
unsigned long mcu_get_dp_download_value(const unsigned char value[],unsigned short len);

/**
 * @brief  串口接收数据暂存处理
 * @param[in] {value} 串口收到的1字节数据
 * @return Null
 * @note   在MCU串口处理函数中调用该函数,并将接收到的数据作为参数传入
 */
void uart_receive_input(unsigned char value);

/**
 * @brief  wifi串口数据处理服务
 * @param  Null
 * @return Null
 * @note   在MCU主函数while循环中调用该函数
 */
void wifi_uart_service(void);

/**
 * @brief  协议串口初始化函数
 * @param  Null
 * @return Null
 * @note   在MCU初始化代码中调用该函数
 */
void wifi_protocol_init(void);

#ifndef WIFI_CONTROL_SELF_MODE
/**
 * @brief  MCU获取复位wifi成功标志
 * @param  Null
 * @return 复位标志
 * -           0(RESET_WIFI_ERROR):失败
 * -           1(RESET_WIFI_SUCCESS):成功
 * @note   1:MCU主动调用mcu_reset_wifi()后调用该函数获取复位状态
 *         2:如果为模块自处理模式,MCU无须调用该函数
 */
unsigned char mcu_get_reset_wifi_flag(void);

/**
 * @brief  MCU主动重置wifi工作模式
 * @param  Null
 * @return Null
 * @note   1:MCU主动调用,通过mcu_get_reset_wifi_flag()函数获取重置wifi是否成功
 *         2:如果为模块自处理模式,MCU无须调用该函数
 */
void mcu_reset_wifi(void);

/**
 * @brief  获取设置wifi状态成功标志
 * @param  Null
 * @return wifimode flag
 * -           0(SET_WIFICONFIG_ERROR):失败
 * -           1(SET_WIFICONFIG_SUCCESS):成功
 * @note   1:MCU主动调用mcu_set_wifi_mode()后调用该函数获取复位状态
 *         2:如果为模块自处理模式,MCU无须调用该函数
 */
unsigned char mcu_get_wifimode_flag(void);

/**
 * @brief  MCU设置wifi工作模式
 * @param[in] {mode} 进入的模式
 * @ref        0(SMART_CONFIG):进入smartconfig模式
 * @ref        1(AP_CONFIG):进入AP模式
 * @return Null
 * @note   1:MCU主动调用
 *         2:成功后,可判断set_wifi_config_state是否为TRUE;TRUE表示为设置wifi工作模式成功
 *         3:如果为模块自处理模式,MCU无须调用该函数
 */
void mcu_set_wifi_mode(unsigned char mode);

/**
 * @brief  MCU主动获取当前wifi工作状态
 * @param  Null
 * @return wifi work state
 * -          SMART_CONFIG_STATE: smartconfig配置状态
 * -          AP_STATE: AP配置状态
 * -          WIFI_NOT_CONNECTED: WIFI配置成功但未连上路由器
 * -          WIFI_CONNECTED: WIFI配置成功且连上路由器
 * -          WIFI_CONN_CLOUD: WIFI已经连接上云服务器
 * -          WIFI_LOW_POWER: WIFI处于低功耗模式
 * -          SMART_AND_AP_STATE: WIFI smartconfig&AP 模式
 * @note   如果为模块自处理模式,MCU无须调用该函数
 */
unsigned char mcu_get_wifi_work_state(void);
#endif

/**
 * @brief  MCU主动获取当前是否允许子设备入网状态
 * @param  Null
 * @return TRUE:允许子设备入网 / FALSE:关闭子设备入网
 * @note   无
 */
unsigned char mcu_get_permit_subdev_netin_state(void);

/**
 * @brief  MCU发送子设备入网请求给WIFI模块。
 * @param[in] {mcu_ver} 子设备的版本号
 * @param[in] {pid} 子设备的pid
 * @param[in] {pk_type} 用户自定义产品类型，可不传(填0代表不传)
 * @param[in] {sub_id_buf} 设备标识，一般为mac地址，芯片id等，需要保证唯一性.不可以是”0000”.”0000”表示网关本身
 * @param[in] {channel} 子设备固件类型，对应于涂鸦云创建产品后上传拓展固件类型；默认10
 * @param[in] {ota} 表示子设备是否支持ota能力  0:表示不支持;  1:表示支持;  默认不支持
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void gateway_subdevice_add(char *mcu_ver,char *pid,unsigned char pk_type,char *sub_id_buf,unsigned char channel,unsigned char ota);

/**
 * @brief  WIFI 模组定时（1-3 分钟）检测子设备在线状态，子设备必须回复心跳，连续两个周期不回复则认为子设备离线
 * @param[in] {sub_id_buf} 设备标识，一般为mac地址，芯片id等，需要保证唯一性.不可以是”0000”.”0000”表示网关本身
 * @param[in] {lowpower_flag} 子设备功耗类型  0：表示为标准功耗设备  1：表示为低功耗设备
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void heart_beat_report(char *sub_id_buf, unsigned char lowpower_flag);

#ifdef SUPPORT_GREEN_TIME
/**
 * @brief  MCU获取格林时间
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void mcu_get_green_time(void);
#endif


#ifdef SUPPORT_MCU_RTC_CHECK
/**
 * @brief  MCU获取系统时间,用于校对本地时钟
 * @param  Null
 * @return Null
 * @note   MCU主动调用完成后在mcu_write_rtctime函数内校对rtc时钟
 */
void mcu_get_system_time(void);
#endif

#ifdef BATCH_ADD_DEV_ENABLE
/**
 * @brief  批量添加子设备
 * @param[in] {cids} 存放子设备id的集合[指针数组]
 * @param[in] {num} 子设备的个数
 * @param[in] {pid} 产品 pid（ProductID），涂鸦云创建产品时生产
 * @param[in] {ver} 版本号，例如"1.0.0"
 * @param[in] {channel} 子设备固件类型，对应于涂鸦云创建产品后上传拓展固件类型；默认10
 * @param[in] {ota} 表示子设备是否支持ota能力  0:表示不支持;  1:表示支持;  默认不支持
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void batch_add_dev(char *cids[], char num, char *pid, char *mcu_ver,unsigned char channel,unsigned char ota);
#endif

#ifdef WIFI_TEST_ENABLE
/**
 * @brief  mcu发起wifi功能测试
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void mcu_start_wifitest(void);
#endif

#ifdef GET_WIFI_STATUS_ENABLE
/**
 * @brief  MCU可根据此条命令获取 WIFI 状态
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void get_wifi_st(void);
#endif

#ifdef RESET_FACTORY_SET_ENABLE
/**
 * @brief  恢复出厂设置
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void reset_factory_setting(void);
#endif

#ifdef LOCAL_SUBDEV_DEL_ENABLE
/**
 * @brief  本地删除子设备(MCU 发送删除子设备指令)
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void local_subdev_del_cmd(char *sub_id);
#endif

#ifdef LOCAL_ADD_SUBDEV_LIMIT_ENABLE
/**
 * @brief  本地允许/关闭添加子设备
 * @param[in] {if_permit}
 * @ref        0:关闭子设备添加
 * @ref        1:允许子设备添加
 * @param[in] {addtime_high} 允许添加时间（高字节）
 * @param[in] {addtime_low} 允许添加时间（低字节）
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void local_add_subdev_limit(unsigned char if_permit,unsigned char addtime_high,unsigned char addtime_low);
#endif

#ifdef GET_MODULE_REMAIN_MEMORY_ENABLE
/**
 * @brief  取 WIFI 模块剩余内存
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void get_module_remain_memory(void);
#endif

#ifdef QUR_SUBDEV_LIST_ENABLE
/**
 * @brief  查询子设备列表
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void qur_subdev_list(void);
#endif

#ifdef UART_CONFIG_INTEGRATED_ENABLE
/**
 * @brief  串口配网（一体式）
 * @param[in] {p_ssid} 热点名称
 * @param[in] {p_password} 热点密码
 * @param[in] {p_token} 由APP生成的token
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void uart_config_intrgrated(char *p_ssid, char *p_password, char *p_token);
#endif

#ifdef UART_CONFIG_DISTRIBUTED_ENABLE
/**
 * @brief  MCU发送配网信息( 串口透传配网(分布式) )
 * @param[in] {p_data} 加密数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void send_config_infor(const unsigned char p_data[], unsigned short data_len);

/**
 * @brief  MCU连接状态( 串口透传配网(分布式) )
 * @param[in] {connect_srate} MCU与手机APP的连接状态
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void mcu_connect_state(unsigned char connect_srate);
#endif

#ifdef UPDATA_SUBDEV_ONLINE_STATE_ENABLE
/**
 * @brief  更新子设备在线/离线状态
 * @param[in] {all} 0:表示不是所有子设备,子设备列表在cids里/1:表示所有子设备,无需传cids这个字段
 * @param[in] {cids} 子设备列表，当all为1时可传NULL
 * @param[in] {send_cids_arr_sz} 子设备个数，当all为1时可传0
 * @param[in] {state} 在线状态: 0:离线/1:在线
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void updata_subden_online_state(unsigned char all, const unsigned char **cids, unsigned char send_cids_arr_sz, unsigned char state);
#endif

#ifdef GET_MODULE_MAC_ENABLE
/**
 * @brief  获取模块的MAC地址
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void get_module_mac(void);
#endif

#ifdef RECORD_STATE_UPLOAD_RT_ENABLE
/**
 * @brief  raw型dp数据上传( 记录型状态实时上报(带时间) )
 * @param[in] {dpid} id号
 * @param[in] {value} 当前dp值指针
 * @param[in] {len} 数据长度
 * @param[in] {sub_id_buf} 存放子设备id的首地址
 * @param[in] {sub_id_len} 子设备id长度
 * @param[in] {p_time_data} 时间数据
 * @param[in] {time_data_len} 时间数据长度
 * @return Null
 * @note   MCU需要自行调用该功能
 */
unsigned char mcu_dp_raw_update_record(unsigned char dpid,const unsigned char value[],unsigned short len,unsigned char *sub_id_buf,unsigned char sub_id_len,  \
                                                          unsigned char p_time_data[], unsigned char time_data_len);

/**
 * @brief  bool型dp数据上传( 记录型状态实时上报(带时间) )
 * @param[in] {dpid} id号
 * @param[in] {value} 当前dp值
 * @param[in] {sub_id_buf} 存放子设备id的首地址
 * @param[in] {sub_id_len} 子设备id长度
 * @param[in] {p_time_data} 时间数据
 * @param[in] {time_data_len} 时间数据长度
 * @return Null
 * @note   MCU需要自行调用该功能
 */
unsigned char mcu_dp_bool_update_record(unsigned char dpid,unsigned char value,unsigned char *sub_id_buf,unsigned char sub_id_len,  \
                                                          unsigned char p_time_data[], unsigned char time_data_len);
/**
 * @brief  value型dp数据上传( 记录型状态实时上报(带时间) )
 * @param[in] {dpid} id号
 * @param[in] {value} 当前dp值
 * @param[in] {sub_id_buf} 存放子设备id的首地址
 * @param[in] {sub_id_len} 子设备id长度
 * @param[in] {p_time_data} 时间数据
 * @param[in] {time_data_len} 时间数据长度
 * @return Null
 * @note   MCU需要自行调用该功能
 */
unsigned char mcu_dp_value_update_record(unsigned char dpid,unsigned long value,unsigned char *sub_id_buf,unsigned char sub_id_len,  \
                                                          unsigned char p_time_data[], unsigned char time_data_len);

/**
 * @brief  string型dp数据上传( 记录型状态实时上报(带时间) )
 * @param[in] {dpid} id号
 * @param[in] {value} 当前dp值指针
 * @param[in] {len} 数据长度
 * @param[in] {sub_id_buf} 存放子设备id的首地址
 * @param[in] {sub_id_len} 子设备id长度
 * @param[in] {p_time_data} 时间数据
 * @param[in] {time_data_len} 时间数据长度
 * @return Null
 * @note   MCU需要自行调用该功能
 */
unsigned char mcu_dp_string_update_record(unsigned char dpid,const unsigned char value[],unsigned short len,unsigned char *sub_id_buf,unsigned char sub_id_len,  \
                                                          unsigned char p_time_data[], unsigned char time_data_len);

/**
 * @brief  enum型dp数据上传( 记录型状态实时上报(带时间) )
 * @param[in] {dpid} id号
 * @param[in] {value} 当前dp值
 * @param[in] {sub_id_buf} 存放子设备id的首地址
 * @param[in] {sub_id_len} 子设备id长度
 * @param[in] {p_time_data} 时间数据
 * @param[in] {time_data_len} 时间数据长度
 * @return Null
 * @note   MCU需要自行调用该功能
 */
unsigned char mcu_dp_enum_update_record(unsigned char dpid,unsigned char value,unsigned char *sub_id_buf,unsigned char sub_id_len,  \
                                                          unsigned char p_time_data[], unsigned char time_data_len);

/**
 * @brief  fault型dp数据上传( 记录型状态实时上报(带时间) )
 * @param[in] {dpid} id号
 * @param[in] {value} 当前dp值
 * @param[in] {sub_id_buf} 存放子设备id的首地址
 * @param[in] {sub_id_len} 子设备id长度
 * @param[in] {p_time_data} 时间数据
 * @param[in] {time_data_len} 时间数据长度
 * @return Null
 * @note   MCU需要自行调用该功能
 */
unsigned char mcu_dp_fault_update_record(unsigned char dpid,unsigned long value,unsigned char *sub_id_buf,unsigned char sub_id_len,  \
                                                          unsigned char p_time_data[], unsigned char time_data_len);
#endif

#ifdef QUERY_SUBDEV_BIND_STATE_ENABLE
/**
 * @brief  查询子设备绑定状态
 * @param[in] {sub_id} 子设备id号
 * @param[in] {d_link} 是否支持双链路（子设备支持手机绑定也支持网关绑定） 0:不支持  1:支持
 * @param[in] {e_val} 加密数值（可选字段，无该字段可忽略）
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void query_subdev_bind_state(char *sub_id, unsigned char d_link, char *e_val);
#endif
  
#ifdef QUERY_GROUP_SUBDEV_ENABLE
/**
 * @brief  查询群组里的子设备
 * @param[in] {str_gid} 群组id
 * @param[in] {idx} 要取群组里的第几个设备，填0就取第一个设备
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void query_group_subdev(char *str_gid, unsigned char idx);
#endif

#ifdef UPLOAD_GROUP_LOCAL_CHANGE_ENABLE
/**
 * @brief  上报群组本地改变的dp
 * @param[in] {str_gid} 群组id
 * @param[in] {dpid} 群组本地有改变的dp,模块收到该dpid后会查询群组设备中的该dp最新状态
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void upload_group_local_change_dp(char *str_gid, unsigned char dpid);
#endif

#ifdef GREEN_TIME_WITH_ZONE_ENABLE
/**
 * @brief  获取带时区系统（格林）时间数据
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void get_green_time_with_zone(void);
#endif

#ifdef HEART_QUERY_MANAGE_ENABLE
/**
 * @brief  心跳查询管理
* @param[in] {heart_ctrl} 心跳控制。0:关闭心跳  1:恢复心跳
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void heart_query_manage(unsigned char heart_ctrl);
#endif

#ifdef SECURITY_PROTECTION_ENABLE
/**
 * @brief  当前布防模式设置
 * @param[in] {str_mode} 布防模式
 * @ref        “0”:disarm撤防（固定不变）
 * @ref        “1”:在家布防
 * @ref        “2”:离家布防
 * @param[in] {str_subid} 触发设置的子设备id
 * @param[in] {delay} 延时布防时间  0:表示以手机设置为主 / 非0:表示延时时间，单位：s
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void defence_mode_set(char *str_mode, char *str_subid, unsigned int delay);

/**
 * @brief  当前安防信息获取
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void security_protect_infor_get(void);

/**
 * @brief  报警状态设置
 * @param[in] {alarm_state} 报警状态 
 * @ref        0：正常
 * @ref        非0：报警中
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void alarm_state_set(unsigned char alarm_state);
#endif


#endif
