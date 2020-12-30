/**********************************Copyright (c)**********************************
**                       版权所有 (C), 2015-2020, 涂鸦科技
**
**                             http://www.tuya.com
**
*********************************************************************************/
/**
 * @file    system.c
 * @author  涂鸦综合协议开发组
 * @version v1.0.6
 * @date    2020.11.11
 * @brief   串口数据处理，用户无需关心该文件实现内容
 */
 

#include "wifi.h"


volatile unsigned char wifi_data_process_buf[PROTOCOL_HEAD + WIFI_DATA_PROCESS_LMT];      //串口数据处理缓存
volatile unsigned char wifi_uart_rx_buf[PROTOCOL_HEAD + WIFI_UART_RECV_BUF_LMT];          //串口接收缓存
volatile unsigned char wifi_uart_tx_buf[PROTOCOL_HEAD + WIFIR_UART_SEND_BUF_LMT];         //串口发送缓存

volatile unsigned char *queue_in = NULL;
volatile unsigned char *queue_out = NULL;

volatile unsigned char stop_update_flag;                                                 //停止一切数据上报
volatile unsigned char stop_subdev_update_flag;                                          //停止正在升级的子设备数据上报

#ifndef WIFI_CONTROL_SELF_MODE
volatile unsigned char reset_wifi_flag;                                                  //重置wifi标志(TRUE:成功/FALSE:失败)
volatile unsigned char set_wifimode_flag;                                                //设置WIFI工作模式标志(TRUE:成功/FALSE:失败)
volatile unsigned char wifi_work_state;                                                  //wifi模块当前工作状态
#endif


extern const DOWNLOAD_CMD_S download_cmd[]; //网关本身的dpid（子设备的dpid需要用户自己根据实际情况管理）
SUBDEV_MANAGE_ST            subdev_manage;//子设备管理结构体
unsigned short firm_size;                                                      //升级包一包的大小

/*设备能力选择*/
/*请在此处选择需要开启的设备的能力，ON为开启，OFF为关闭*/
tSUB_ABILITY sub_ability = {
    OFF,        //本地群组
    OFF,        //本地场景
    ON,         //网关有功能dp
    OFF,        //sigmesh
    OFF,        //支持mcu升级
    OFF,        //群组控制指令带sub_id
    OFF,        //蓝牙串口配网
    OFF         //取消心跳包
};



/**
 * @brief  写wifi_uart字节
 * @param[in] {dest} 缓存区地址偏移
 * @param[in] {byte} 写入字节值
 * @return 写入完成后的总长度
 */
unsigned short set_wifi_uart_byte(unsigned short dest, unsigned char byte)
{
    unsigned char *obj = (unsigned char *)wifi_uart_tx_buf + DATA_START + dest;
    
    *obj = byte;
    dest += 1;
    
    return dest;
}

/**
 * @brief  写wifi_uart_buffer
 * @param[in] {dest} 缓存区地址偏移
 * @param[in] {src} 源地址（需要发送的数据）
 * @param[in] {len} 需要发送的数据长度
 * @return 写入完成后的总长度
 */
unsigned short set_wifi_uart_buffer(unsigned short dest, const unsigned char *src, unsigned short len)
{
    if(NULL == src) {
        return dest;
    }
    unsigned char *obj = (unsigned char *)wifi_uart_tx_buf + DATA_START + dest;
    
    my_memcpy(obj,src,len);
    
    dest += len;
    return dest;
}

/**
 * @brief  计算校验和
 * @param[in] {pack} 数据源指针
 * @param[in] {pack_len} 计算校验和长度
 * @return 校验和
 */
unsigned char get_check_sum(unsigned char *pack, unsigned short pack_len)
{
    unsigned short i;
    unsigned char check_sum = 0;
    
    for(i = 0; i < pack_len; i ++) {
        check_sum += *pack ++;
    }
    
    return check_sum;
}

/**
 * @brief  串口发送一段数据
 * @param[in] {in} 发送缓存指针
 * @param[in] {len} 数据发送长度
 * @return Null
 */
static void wifi_uart_write_data(unsigned char *in, unsigned short len)
{
    if((NULL == in) || (0 == len)) {
        return;
    }
    
    while(len --) {
        uart_transmit_output(*in);
        in ++;
    }
}

/**
 * @brief  向wifi串口发送一帧数据
 * @param[in] {fr_type} 帧类型
 * @param[in] {fr_ver} 帧版本
 * @param[in] {len} 数据长度
 * @return Null
 */
void wifi_uart_write_frame(unsigned char fr_type, unsigned char fr_ver, unsigned short len)
{
    unsigned char check_sum = 0;
    
    wifi_uart_tx_buf[HEAD_FIRST] = 0x55;
    wifi_uart_tx_buf[HEAD_SECOND] = 0xaa;
    wifi_uart_tx_buf[PROTOCOL_VERSION] = fr_ver;
    wifi_uart_tx_buf[FRAME_TYPE] = fr_type;
    wifi_uart_tx_buf[LENGTH_HIGH] = len >> 8;
    wifi_uart_tx_buf[LENGTH_LOW] = len & 0xff;
    
    len += PROTOCOL_HEAD;
    check_sum = get_check_sum((unsigned char *)wifi_uart_tx_buf, len - 1);
    wifi_uart_tx_buf[len - 1] = check_sum;
    //
    wifi_uart_write_data((unsigned char *)wifi_uart_tx_buf, len);
}

/**
 * @brief  产品信息上传
 * @param[in] {pid_flag} 是否上传产品pid
 * @ref           0x00: 不上传
 * @ref           0x01: 上传
 * @return Null
 */
static void product_info_update(unsigned char pid_flag)
{
    unsigned char length = 0;
    unsigned char a = 0;
    
    cJSON *root = NULL;
     
    root = cJSON_CreateObject();
    if(NULL == root) {
        //可在此添加提示信息，如：printf("xxx");
        return;
    }
    
    cJSON_AddStringToObject(root, "v", MCU_VER);
    cJSON_AddNumberToObject(root, "m", CONFIG_MODE);
    cJSON_AddNumberToObject(root, "cap", sub_ability.whole);
    if(0x01 == pid_flag) {
        cJSON_AddStringToObject(root, "p", PRODUCT_KEY);
    }
#ifdef CONFIG_MODE_CHOOSE
    cJSON_AddNumberToObject(root, "n", CONFIG_MODE_CHOOSE);
#endif
  
#ifdef SECURITY_PROTECTION_ENABLE
    cJSON_AddNumberToObject(root, "s", 1);
#else
    cJSON_AddNumberToObject(root, "s", 0);
#endif
    
#ifdef SECURITY_PROTECTION_ALARM_DISPLAY_ENABLE
    a |= 0x01;
#endif
    
    if(0 != a) {
        cJSON_AddNumberToObject(root, "a", a);
    }

    char* out = cJSON_PrintUnformatted(root);
    
    cJSON_Delete(root);
    
    if(NULL == out) {
        //可在此添加提示信息，如：printf("xxx");
        return;
    }
    
    length = set_wifi_uart_buffer(length, out, my_strlen(out));

    wifi_uart_write_frame(PRODUCT_INFO_CMD, MCU_TX_VER, length);

    free(out);
}

/**
 * @brief  mcu查询mcu和wifi的工作模式
 * @param  Null
 * @return Null
 */
static void get_mcu_wifi_mode(void)
{
    unsigned char length = 0;
    
#ifdef WIFI_CONTROL_SELF_MODE                                   //模块自处理
    length = set_wifi_uart_byte(length, WF_LED_PORT);
    length = set_wifi_uart_byte(length, WF_LED_PIN);
    length = set_wifi_uart_byte(length, WF_RESERT_KEY_PORT);
    length = set_wifi_uart_byte(length, WF_RESERT_KEY_PIN);
#else                                                           
    //无需处理数据
#endif
  
    wifi_uart_write_frame(WORK_MODE_CMD, MCU_TX_VER, length);
}

/**
 * @brief  获取制定DPID在数组中的序号
 * @param[in] {dpid} dpid
 * @return dp序号
 */
unsigned char get_dowmload_dpid_index(unsigned char dpid)
{
    unsigned char index;
    unsigned char total = get_download_cmd_total();
    
    for(index = 0; index < total; index ++) {
        if(download_cmd[index].dp_id == dpid) {
            break;
        }
    }
    
    return index;
}

/**
 * @brief  根据子设备id进行下发数据处理
 * @param[in] {value} 下发数据源指针
 * @param[in] {sub_id_buf} 子设备的sun_id,决定数据发送置哪个子设备
 * @param[in] {sub_id_len} 子设备的sun_id长度
 * @return 返回数据处理结果
 */
static unsigned char data_point_handle(const unsigned char value[],unsigned char* sub_id_buf,unsigned char sub_id_len)
{
    //这边是数据下发函数，请根据实际情况调用
    unsigned char dp_id,index;
    unsigned char dp_type;
    unsigned char ret;
    unsigned short dp_len;
    
    dp_id = value[0];
    dp_type = value[1];
    dp_len = (value[2] <<8) + value[3];
    
    index = get_dowmload_dpid_index(dp_id);
      
    if(dp_type != download_cmd[index].dp_type) {
        //错误提示
        return FALSE;
    }else {
        //请根据dpid自行做出不同子设备的dp处理
        //请根据sub_id来决定给哪个子设备下发数据
        //请在该函数根据子设备的id自行实现子设备的dpid处理，"0000"代表的是需要进行下发数据处理的是网关本身
        ret = dp_download_handle(dp_id, value + 4, dp_len, sub_id_buf, sub_id_len);
    }
    
    return ret;
}

#ifdef WEATHER_ENABLE
/**
 * @brief  天气数据解析
 * @param[in] {p_data} 接收数据指针
 * @param[in] {data_len} 接收数据长度
 * @return Null
 */
static void weather_data_raw_handle(const unsigned char p_data[], unsigned short data_len)
{
    unsigned short send_len = 0;
    int i = 1;
    int param_len_L = 0; 
    char param_K[20] = {0};
    char day = 0;
    int type_T = 0;
    unsigned char value_string[100] = {0};
    int val_cnt = 0;
    int val_len = 0;
    
    if(p_data[0] != 1 || data_len < 1) {
        //接收失败
        
        return;
    }
    
    while (i < data_len) {
        param_len_L = p_data[i];
        
        my_memset(param_K, '\0', sizeof(param_K));
        my_memcpy(param_K, p_data + i + 1, param_len_L - 2);

        day = p_data[i + param_len_L] - '0';

        type_T = p_data[i + 1 + param_len_L];
        if(type_T != 0 && type_T != 1) {
            //数据类型错误
            
            return;
        }

        val_cnt = i + 1 + param_len_L + 1;
        val_len = p_data[val_cnt];
        if (type_T == 0) { //int32
            weather_data_user_handle(param_K+2, type_T, p_data+val_cnt+1, day);
        }
        else if(type_T == 1) { //string
            my_memset(value_string, '\0', 100);
            my_memcpy(value_string, p_data + val_cnt + 1, val_len);
            weather_data_user_handle(param_K+2, type_T, value_string, day);
        }

        i += 1 + param_len_L + 1 + 1 + val_len;
    }
    
    send_len = set_wifi_uart_byte(send_len, WEATHER_DATA_SUBCMD);
    wifi_uart_write_frame(EXPAND_FUNC_CMD, MCU_TX_VER, send_len);
    
}
#endif

/**
 * @brief  数据帧处理
 * @param[in] {offset} 数据起始位
 * @return Null
 */
void data_handle(unsigned short offset)
{
    unsigned char *firmware_addr = NULL;
    static unsigned long firm_length;                          //MCU升级文件长度
    static unsigned char firm_update_flag;                     //MCU升级标志
    unsigned long dp_len_up;                                   //mcu升级的dplen
    unsigned char firm_flag;                                   //升级包大小标志

    unsigned short dp_len;

    unsigned char ret = 0;
    unsigned short i,total_len;
    unsigned char cmd_type = wifi_data_process_buf[offset + FRAME_TYPE];
    unsigned char result;

    /*子设备id和群组id*/
    unsigned char sub_id_len = 0;                              //子设备id长度
    unsigned char grp_id_len = 0;                              //群组id长度
    unsigned char grp_id_buf[BUF_SIZE];                        //群组id
    unsigned char sub_id_buf[BUF_SIZE];                        //子设备id

    unsigned char *dest = NULL;
    unsigned int module_memory;
    
#ifdef WEATHER_ENABLE
    static unsigned char isWoSend = 0;                         //是否已经打开过天气数据, 0:否  1:是
#endif

#ifdef WIFI_TEST_ENABLE
    unsigned char rssi;
#endif
  
    switch(cmd_type) {
        case PRODUCT_INFO_CMD:                                //产品信息
            product_info_update(wifi_data_process_buf[offset + PROTOCOL_VERSION]);
        break;
          
        case WORK_MODE_CMD:                                   //查询MCU设定的模块工作模式
            get_mcu_wifi_mode();
        break;
          
#ifndef WIFI_CONTROL_SELF_MODE
        case WIFI_STATE_CMD:                                  //wifi联网状态
            wifi_work_state = wifi_data_process_buf[offset + DATA_START]; //记录模块当前联网状态
            wifi_uart_write_frame(WIFI_STATE_CMD, MCU_TX_VER, 0);
#ifdef WEATHER_ENABLE
            if(wifi_work_state == WIFI_CONNECTED && isWoSend == 0) { //当WIFI连接成功，打开天气数据且仅一次
                mcu_open_weather();
                isWoSend = 1;
            }
#endif
        
        break;

        case WIFI_RESET_CMD:                                  //重置wifi(wifi返回成功)
            reset_wifi_flag = RESET_WIFI_SUCCESS;
        break;
          
        case WIFI_MODE_CMD:                                   //选择smartconfig/AP模式(wifi返回成功)
            set_wifimode_flag = SET_WIFICONFIG_SUCCESS;
        break;
#endif

        case PERMIT_SUBDEVICE_NETIN_CMD:                      //允许子设备入网
            //TRUE则说明子设备允许入网，用户可根据这个标志位判断子设备是否允许入网
            subdev_manage.if_subdev_net_in = TRUE;
            wifi_uart_write_frame(PERMIT_SUBDEVICE_NETIN_CMD, MCU_TX_VER, 0);
        break;

        case CLOSE_SUBDEVICE_NETIN_CMD:                       //关闭子设备入网
            //FALSE说明拒绝子设备入网，用户可根据这个标志位判断子设备是否允许入网
            subdev_manage.if_subdev_net_in = FALSE;
            wifi_uart_write_frame(CLOSE_SUBDEVICE_NETIN_CMD, MCU_TX_VER, 0);
        break;

        case SUBDEVICE_ADD_CMD:                               //子设备添加
            result = wifi_data_process_buf[offset + DATA_START];
            subdevice_add_result(result);
        break;

        case SUBDEVICE_DELETTE_CMD:                           //子设备删除
            total_len = (wifi_data_process_buf[offset + LENGTH_HIGH] << 8) | wifi_data_process_buf[offset + LENGTH_LOW];
            subdevice_delete((unsigned char *)&wifi_data_process_buf[offset + DATA_START],total_len);
            wifi_uart_write_frame(SUBDEVICE_DELETTE_CMD, MCU_TX_VER, 0);
        break;

        case HEART_CHECK_CMD:                                 //心跳检测
            total_len = (wifi_data_process_buf[offset + LENGTH_HIGH] << 8) | wifi_data_process_buf[offset + LENGTH_LOW];
            heart_beat_check((unsigned char *)&wifi_data_process_buf[offset + DATA_START],total_len);
        break;
          
        case STATE_QUERY_CMD:                                 //状态查询
            all_data_update();                               
        break;

        case DATA_ISSUED_CMD:                                 //命令下发
            total_len = (wifi_data_process_buf[offset + LENGTH_HIGH] << 8) | wifi_data_process_buf[offset + LENGTH_LOW];
            sub_id_len = wifi_data_process_buf[offset + DATA_START];
            
            my_memset(sub_id_buf, 0x00, BUF_SIZE);
            my_memcpy(sub_id_buf, (unsigned char *)&wifi_data_process_buf[offset + DATA_START + 1], sub_id_len);
          
            for(i = 1 + sub_id_len;i < total_len; ) {
                dp_len = (wifi_data_process_buf[offset + DATA_START + i + 2] << 8) | wifi_data_process_buf[offset + DATA_START + i + 3];

                ret = data_point_handle((unsigned char *)wifi_data_process_buf + offset + DATA_START + i, sub_id_buf, sub_id_len);

                if(SUCCESS == ret) {
                    //成功提示
                }else {
                    //错误提示
                }
                
                i += (dp_len + 4);
            }
        break;
          
#ifdef GROUP_SUBDEV_ENABLE
        case GROUP_SUBDEV_ADD_CMD:                              //群组子设备加入
            total_len = (wifi_data_process_buf[offset + LENGTH_HIGH] << 8) | wifi_data_process_buf[offset + LENGTH_LOW];
            group_subdev_add((unsigned char *)(wifi_data_process_buf + offset + DATA_START), total_len);
        break;
        
        case GROUP_SUBDEV_DEL_CMD:                              //群组子设备删除
            total_len = (wifi_data_process_buf[offset + LENGTH_HIGH] << 8) | wifi_data_process_buf[offset + LENGTH_LOW];
            group_subdev_del((unsigned char *)(wifi_data_process_buf + offset + DATA_START), total_len);
        break;
#endif 
          
#ifdef SUPPORT_GREEN_TIME
        case GET_ONLINE_TIME_CMD:                              //获取格林时间
            mcu_get_greentime((unsigned char *)(wifi_data_process_buf + offset + DATA_START));
        break;
#endif
        
#ifdef SUPPORT_MCU_RTC_CHECK
        case GET_LOCAL_TIME_CMD:                               //获取本地时间
            mcu_write_rtctime((unsigned char *)(wifi_data_process_buf + offset + DATA_START));
        break;
#endif

#ifdef BATCH_ADD_DEV_ENABLE
        case BATCH_ADD_DEV_CMD:                                //批量添加设备
            result = wifi_data_process_buf[offset + DATA_START];
            batch_add_dev_result(result);
        break;

        case ADD_DEV_RESULT_CMD:                               //返回添加设备结果
            total_len = (wifi_data_process_buf[offset + LENGTH_HIGH] << 8) | wifi_data_process_buf[offset + LENGTH_LOW];
            add_dev_result_get((unsigned char *)&wifi_data_process_buf[offset + DATA_START],total_len);
        break;
#endif
        
#ifdef CTRL_GROUP_DOWNLOAD_ENABLE
        case CTRL_GROUP_DOWNLOAD_CMD:                      //控制群组指令下发
            total_len = (wifi_data_process_buf[offset + LENGTH_HIGH] << 8) | wifi_data_process_buf[offset + LENGTH_LOW];
            grp_id_len = wifi_data_process_buf[offset + DATA_START];
            
            my_memset(grp_id_buf, 0x00, BUF_SIZE);
            my_memcpy(grp_id_buf, (unsigned char *)&wifi_data_process_buf[offset + DATA_START + 1], grp_id_len);

            for(i = 1 + grp_id_len;i < total_len;) {
                dp_len = (wifi_data_process_buf[offset + DATA_START + i + 2] << 8) | wifi_data_process_buf[offset + DATA_START + i + 3];
                
                ret = ctrl_group_issued((unsigned char *)wifi_data_process_buf + offset + DATA_START + i,grp_id_buf,grp_id_len);

                if(SUCCESS == ret) {
                    //成功提示
                }else {
                    //错误提示
                }
                
                i += (dp_len + 4);
            }
            
            wifi_uart_write_frame(CTRL_GROUP_DOWNLOAD_CMD, MCU_TX_VER, 0);
        break;
#endif

#ifdef WIFI_TEST_ENABLE
        case WIFI_TEST_CMD:                                   //wifi功能测试（扫描指定路由）
            result = wifi_data_process_buf[offset + DATA_START];
            rssi = wifi_data_process_buf[offset + DATA_START + 1];
            
            wifi_test_result(result, rssi);
        break;
#endif

#ifdef GET_WIFI_STATUS_ENABLE
        case GET_WIFI_STATUS_CMD:                               //获取wifi状态
              result = wifi_data_process_buf[offset + DATA_START];
              wifi_status_result(result);
        break;
#endif

#ifdef INFORM_DEV_DEV_DEL_ENABLE
        case INFORM_DEV_DEV_DEL_CMD:                            //报告移除状态
            result = wifi_data_process_buf[offset + DATA_START];
            inform_dev_del_status(result);
        break;
#endif
        
#ifdef LOCAL_SUBDEV_DEL_ENABLE
        case LOCAL_SUBDEV_DEL_CMD:                              //本地删除子设备
            result = wifi_data_process_buf[offset + DATA_START];
            local_del_subdev(result);
        break;
#endif

#ifdef LOCAL_ADD_SUBDEV_LIMIT_ENABLE
        case LOCAL_ADD_SUBDEV_LIMIT_CMD:                        //本地允许/关闭添加子设备
            result = wifi_data_process_buf[offset + DATA_START];
            local_subdev_limit(result);
        break;
#endif

#ifdef GET_MODULE_REMAIN_MEMORY_ENABLE
        case GET_MODULE_REMAIN_MEMORY_CMD:                      //获取模块内存
            module_memory = wifi_data_process_buf[offset + DATA_START] << 3;
            module_memory += wifi_data_process_buf[offset + DATA_START + 1] << 2;
            module_memory += wifi_data_process_buf[offset + DATA_START + 2] << 1;
            module_memory += wifi_data_process_buf[offset + DATA_START + 3] << 0;

            remain_memory_result(module_memory);
        break;
#endif

#ifdef QUR_SUBDEV_LIST_ENABLE
        case QUR_SUBDEV_LIST_CMD:                               //查询子设备列表
            total_len = (wifi_data_process_buf[offset + LENGTH_HIGH] << 8) | wifi_data_process_buf[offset + LENGTH_LOW];
            local_subdev_list((unsigned char *)&wifi_data_process_buf[offset + DATA_START],total_len);
        break;
#endif

#ifdef SUPPORT_MCU_FIRM_UPDATE
        case UPDATE_START_CMD:                                //升级开始
            //升级包单包大小
            firm_flag = PACKAGE_SIZE;
            if(firm_flag == 0) {
                firm_size = 256;
            }else if(firm_flag == 1) {
                firm_size = 512;
            }else if(firm_flag == 2) { 
                firm_size = 1024;
            }

            //升级文件大小
            firm_length = wifi_data_process_buf[offset + DATA_START];
            firm_length <<= 8;
            firm_length |= wifi_data_process_buf[offset + DATA_START + 1];
            firm_length <<= 8;
            firm_length |= wifi_data_process_buf[offset + DATA_START + 2];
            firm_length <<= 8;
            firm_length |= wifi_data_process_buf[offset + DATA_START + 3];

            upgrade_package_choose(PACKAGE_SIZE);
            firm_update_flag = UPDATE_START_CMD;
        break;

        case UPDATE_TRANS_CMD:                                //升级传输
            if(firm_update_flag == UPDATE_START_CMD) {
                //停止一切数据上报
                stop_update_flag = ENABLE;                                                 

                //一包数据总长度
                total_len = (wifi_data_process_buf[offset + LENGTH_HIGH] << 8) | wifi_data_process_buf[offset + LENGTH_LOW];

                //包偏移
                dp_len_up = wifi_data_process_buf[offset + DATA_START];
                dp_len_up <<= 8;
                dp_len_up |= wifi_data_process_buf[offset + DATA_START + 1];
                dp_len_up <<= 8;
                dp_len_up |= wifi_data_process_buf[offset + DATA_START + 2];
                dp_len_up <<= 8;
                dp_len_up |= wifi_data_process_buf[offset + DATA_START + 3];

                //数据包
                firmware_addr = (unsigned char *)wifi_data_process_buf;
                firmware_addr += (offset + DATA_START + 4);  //数据包内容起始地址
                //没有数据内容或者包偏移等于升级文件大小（数据发送完成）
                if((total_len == 4) && (dp_len_up == firm_length)) {
                    //最后一包（代表数据发送完成）
                    ret = mcu_firm_update_handle(firmware_addr,dp_len_up,0);
                    
                    firm_update_flag = 0;
                }else if((total_len - 4) <= firm_size) { //数据pack里面还有数据
                    //数据未发送完成，进行数据处理
                    ret = mcu_firm_update_handle(firmware_addr,dp_len_up,total_len - 4);
                }else {
                    firm_update_flag = 0;
                    ret = ERROR;
                }

                if(ret == SUCCESS) {
                    wifi_uart_write_frame(UPDATE_TRANS_CMD, MCU_TX_VER, 0);
                }
                //恢复一切数据上报
                stop_update_flag = DISABLE;    
            }
        break;

        case SUBDEV_START_UPGRADE_CMD:                          //子设备启动升级
            //获取升级包大小全局变量
            firm_flag = PACKAGE_SIZE;
            if(firm_flag == 0) {
                firm_size = 256;
            }else if(firm_flag == 1) {
                firm_size = 512;
            }else if(firm_flag == 2) { 
                firm_size = 1024;
            }
            
            sub_id_len = wifi_data_process_buf[offset + DATA_START];
            
            my_memset(sub_id_buf, 0x00, BUF_SIZE);
            my_memcpy(sub_id_buf, (unsigned char *)&wifi_data_process_buf[offset + DATA_START + 1], sub_id_len);
            
            //用户根据子设备id选择要升级的子设备
            firm_length = wifi_data_process_buf[offset + DATA_START + 1 + sub_id_len];
            firm_length <<= 8;
            firm_length |= wifi_data_process_buf[offset + DATA_START + 1 + 1 + sub_id_len];
            firm_length <<= 8;
            firm_length |= wifi_data_process_buf[offset + DATA_START + 2 + 1 + sub_id_len];
            firm_length <<= 8;
            firm_length |= wifi_data_process_buf[offset + DATA_START + 3 + 1 + sub_id_len];
            
            subdev_upgrade_package_choose(PACKAGE_SIZE,sub_id_buf,sub_id_len);
            firm_update_flag = SUBDEV_START_UPGRADE_CMD;
        break;

        case SUBDEV_TRANS_CMD:                                  //子设备升级包传输
            if(firm_update_flag == SUBDEV_START_UPGRADE_CMD) {
                //停止一切数据上报
                stop_update_flag = ENABLE;

                total_len = (wifi_data_process_buf[offset + LENGTH_HIGH] << 8) | wifi_data_process_buf[offset + LENGTH_LOW];
                
                sub_id_len = wifi_data_process_buf[offset + DATA_START];
                my_memset(sub_id_buf, 0x00, BUF_SIZE);
                my_memcpy(sub_id_buf, (unsigned char *)&wifi_data_process_buf[offset + DATA_START + 1], sub_id_len);
                
                dp_len_up = wifi_data_process_buf[offset + DATA_START + 1 + sub_id_len];
                dp_len_up <<= 8;
                dp_len_up |= wifi_data_process_buf[offset + DATA_START + 1 + 1 + sub_id_len];
                dp_len_up <<= 8;
                dp_len_up |= wifi_data_process_buf[offset + DATA_START + 2 + 1 + sub_id_len];
                dp_len_up <<= 8;
                dp_len_up |= wifi_data_process_buf[offset + DATA_START + 3 + 1 + sub_id_len];
                
                firmware_addr = (unsigned char *)wifi_data_process_buf;
                firmware_addr += (offset + DATA_START + 4 + 1 + sub_id_len);  //数据包内容起始地址
                if((total_len == 4 + 1 + sub_id_len) && (dp_len_up == firm_length)) {
                    //最后一包
                    ret = subdev_firm_update_handle(sub_id_buf,firmware_addr,dp_len_up,0);
                    
                    firm_update_flag = 0;
                }else if((total_len - 4 - sub_id_len - 1) <= firm_size) {
                    ret = subdev_firm_update_handle(sub_id_buf,firmware_addr,dp_len_up,total_len - 4- sub_id_len - 1);
                }else {
                    firm_update_flag = 0;
                    ret = ERROR;
                }
                
                if(ret == SUCCESS) {
                    wifi_uart_write_frame(SUBDEV_TRANS_CMD, MCU_TX_VER, 0);
                }
                //恢复一切数据上报
                stop_update_flag = DISABLE;    
            }
        break;
          
        case QUR_SUBDEV_VER_CMD:                              //查询子设备版本号
            total_len = (wifi_data_process_buf[offset + LENGTH_HIGH] << 8) | wifi_data_process_buf[offset + LENGTH_LOW];
            qur_subdev_ver_get((unsigned char *)&wifi_data_process_buf[offset + DATA_START],total_len);
        break;
#endif

#ifdef CTRL_GROUP_DOWNLOAD_SUB_ID_ENABLE
        case CTRL_GROUP_DOWNLOAD_SUB_CMD:                      //控制群组指令下发(带sub_id)
            total_len = (wifi_data_process_buf[offset + LENGTH_HIGH] << 8) | wifi_data_process_buf[offset + LENGTH_LOW];
            
            grp_id_len = wifi_data_process_buf[offset + DATA_START];
            my_memset(grp_id_buf, 0x00, BUF_SIZE);
            my_memcpy(grp_id_buf, (unsigned char *)&wifi_data_process_buf[offset + DATA_START + 1], grp_id_len);
          
            sub_id_len = wifi_data_process_buf[offset + DATA_START + 1 + grp_id_len];
            my_memset(sub_id_buf, 0x00, BUF_SIZE);
            my_memcpy(sub_id_buf, (unsigned char *)&wifi_data_process_buf[offset + DATA_START + 2 + grp_id_len], sub_id_len);

            for(i = 2 + grp_id_len + sub_id_len; i < total_len; ) {
                dp_len = (wifi_data_process_buf[offset + DATA_START + i + 2] << 8) | wifi_data_process_buf[offset + DATA_START + i + 3];
                
                ret = ctrl_group_issued_sub_id((unsigned char *)wifi_data_process_buf + offset + DATA_START + i, grp_id_buf, grp_id_len, sub_id_buf, sub_id_len);

                if(SUCCESS == ret) {
                    //成功提示
                }else {
                    //错误提示
                }
                
                i += (dp_len + 4);
            }
            
            wifi_uart_write_frame(CTRL_GROUP_DOWNLOAD_SUB_CMD, MCU_TX_VER, 0);
        break;
#endif
          
#ifdef UART_CONFIG_INTEGRATED_ENABLE
        case UART_CONFIG_CMD:                                   //串口配网（一体式）
            result = wifi_data_process_buf[offset + DATA_START];
            uart_config_intrgrated_result(result);
        break;
#endif
        
#ifdef UART_CONFIG_DISTRIBUTED_ENABLE
        case SEND_BROAD_PACKET_CMD:                             //WIFI发送广播包( 串口透传配网(分布式) )
            total_len = (wifi_data_process_buf[offset + LENGTH_HIGH] << 8) | wifi_data_process_buf[offset + LENGTH_LOW];
            send_broad_packet((unsigned char *)wifi_data_process_buf + offset + DATA_START, total_len);
        break;

        case UPLOAD_CONFIG_INFOR_CMD:                             //WIFI上报配网信息( 串口透传配网(分布式) )
            total_len = (wifi_data_process_buf[offset + LENGTH_HIGH] << 8) | wifi_data_process_buf[offset + LENGTH_LOW];
            upload_config_infor((unsigned char *)wifi_data_process_buf + offset + DATA_START, total_len);
        break;

        case WIFI_DISCONNECT_CMD:                               //wifi模块主动断开连接( 串口透传配网(分布式) )
            wifi_disconnect();
        break;
#endif
        
        
#ifdef GET_DP_STATE_ENABLE
        case GET_DP_STATE_CMD:                                  //查询dp状态
            total_len = (wifi_data_process_buf[offset + LENGTH_HIGH] << 8) | wifi_data_process_buf[offset + LENGTH_LOW];
            get_dp_state((unsigned char *)wifi_data_process_buf + offset + DATA_START, total_len);
        break;
#endif

#ifdef UPDATA_SUBDEV_ONLINE_STATE_ENABLE
        case UPDATA_SUBDEV_ONLINE_STATE_CMD:                    //更新子设备在线/离线状态
            result = wifi_data_process_buf[offset + DATA_START];
            updata_subden_online_state_result(result);
        break;
#endif

#ifdef GET_MODULE_MAC_ENABLE
        case GET_MODULE_MAC_CMD:                                //获取模块的MAC地址
            get_module_mac_result((unsigned char *)wifi_data_process_buf + offset + DATA_START);
        break;
#endif

#ifdef RECORD_STATE_UPLOAD_RT_ENABLE
        case RECORD_STATE_UPLOAD_RT_CMD:                        //记录型状态实时上报（带时间）
            result = wifi_data_process_buf[offset + DATA_START];
            record_state_upload_rt_result(result);
        break;
#endif
        
#ifdef QUERY_SUBDEV_BIND_STATE_ENABLE
        case QUERY_SUBDEV_BIND_STATE_CMD:                        //查询子设备绑定状态
            total_len = (wifi_data_process_buf[offset + LENGTH_HIGH] << 8) | wifi_data_process_buf[offset + LENGTH_LOW];
            query_subdev_bind_state_result((unsigned char *)wifi_data_process_buf + offset + DATA_START, total_len);
        break;
#endif

#ifdef QUERY_GROUP_SUBDEV_ENABLE
        case QUERY_GROUP_SUBDEV_CMD:                              //查询群组里的子设备
            total_len = (wifi_data_process_buf[offset + LENGTH_HIGH] << 8) | wifi_data_process_buf[offset + LENGTH_LOW];
            query_group_subdev_result((unsigned char *)wifi_data_process_buf + offset + DATA_START, total_len);
        break;
#endif

#ifdef UPLOAD_GROUP_LOCAL_CHANGE_ENABLE
        case UPLOAD_GROUP_LOCAL_CHANGE_CMD:                       //上报群组本地改变的dp
            result = wifi_data_process_buf[offset + DATA_START];
            upload_group_local_change_dp_result(result);
        break;
#endif
        
#ifdef IR_CTRL_ENABLE
        case IR_CTRL_CMD_SEND_CMD:                              //红外类控制码发送
            total_len = (wifi_data_process_buf[offset + LENGTH_HIGH] << 8) | wifi_data_process_buf[offset + LENGTH_LOW];
            ir_ctrl_cmd_send((unsigned char *)wifi_data_process_buf + offset + DATA_START, total_len);
        break;
        
        case IR_CTRL_CMD_LEARN_CMD:                             //红外类控制码学习
            total_len = (wifi_data_process_buf[offset + LENGTH_HIGH] << 8) | wifi_data_process_buf[offset + LENGTH_LOW];
            ir_ctrl_cmd_learn((unsigned char *)wifi_data_process_buf + offset + DATA_START, total_len);
        break;
        
        case IR_CTRL_CMD_CANCEL_LEARN_CMD:                      //红外类控制码取消学习
            ir_ctrl_cmd_cancel_learn();
        break;
#endif

        case EXPAND_FUNC_CMD:                                   //拓展功能
            switch(wifi_data_process_buf[offset + DATA_START]) { //子命令
#ifdef WEATHER_ENABLE
                case OPEN_WEATHER_SUBCMD:                       //打开天气服务返回
                    weather_open_return_handle(wifi_data_process_buf[offset + DATA_START + 1], wifi_data_process_buf[offset + DATA_START + 2]);
                break;
            
                case WEATHER_DATA_SUBCMD:                       //天气数据下发
                    total_len = (wifi_data_process_buf[offset + LENGTH_HIGH] << 8) | wifi_data_process_buf[offset + LENGTH_LOW];
                    weather_data_raw_handle((unsigned char *)wifi_data_process_buf + offset + DATA_START + 1, total_len - 1);
                break;
                
                case GET_WEATHER_SUBCMD:                        //MCU主动获取天气数据
                    mcu_get_weather_result(wifi_data_process_buf[offset + DATA_START + 1]);
                break;
#endif

#ifdef GREEN_TIME_WITH_ZONE_ENABLE
                case GET_GREEN_TIME_WITH_ZONE_SUBCMD:           //带时区系统（格林）时间数据下发
                    total_len = (wifi_data_process_buf[offset + LENGTH_HIGH] << 8) | wifi_data_process_buf[offset + LENGTH_LOW];
                    get_green_time_with_zone_result((unsigned char *)wifi_data_process_buf + offset + DATA_START + 1, total_len - 1);
                break;
#endif

#ifdef HEART_QUERY_MANAGE_ENABLE
                case HEART_QUERY_MANAGE_SUBCMD:                 //心跳查询管理
                    //无需处理
                break;
#endif
                default:break;
            }
        break;
        
#ifdef SECURITY_PROTECTION_ENABLE
        case SECURITY_PROTECT_INFOR_CMD:                          //安防信息
            total_len = (wifi_data_process_buf[offset + LENGTH_HIGH] << 8) | wifi_data_process_buf[offset + LENGTH_LOW];
            security_protect_infor_result((unsigned char *)wifi_data_process_buf + offset + DATA_START, total_len);
        break;
        
        case SECURITY_PROTECT_ALARM_CMD:                          //安防报警
            total_len = (wifi_data_process_buf[offset + LENGTH_HIGH] << 8) | wifi_data_process_buf[offset + LENGTH_LOW];
            alarm_infor_result((unsigned char *)wifi_data_process_buf + offset + DATA_START, total_len);
        break;
#endif
        
        
        default:
        break;
    }
}

/**
 * @brief  判断串口接收缓存中是否有数据
 * @param  Null
 * @return 是否有数据  0:无/1:有
 */
unsigned char get_queue_total_data(void)
{
  if(queue_in != queue_out)
    return 1;
  else
    return 0;
}

/**
 * @brief  读取队列1字节数据
 * @param  Null
 * @return Read the data
 */
unsigned char Queue_Read_Byte(void)
{
  unsigned char value;
  
  if(queue_out != queue_in)
  {
    //有数据
    if(queue_out >= (unsigned char *)(wifi_uart_rx_buf + sizeof(wifi_uart_rx_buf)))
    {
      //数据已经到末尾
      queue_out = (unsigned char *)(wifi_uart_rx_buf);
    }
    
    value = *queue_out ++;   
  }
  
  return value;
}

