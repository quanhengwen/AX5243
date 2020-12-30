/**********************************Copyright (c)**********************************
**                       版权所有 (C), 2015-2020, 涂鸦科技
**
**                             http://www.tuya.com
**
*********************************************************************************/
/**
 * @file    protocol.c
 * @author  涂鸦综合协议开发组
 * @version v1.0.6
 * @date    2020.11.11
 * @brief                
 *                       *******非常重要，一定要看哦！！！********
 *          1. 用户在此文件中实现数据下发/上报功能
 *          2. DP的ID/TYPE及数据处理函数都需要用户按照实际定义实现
 *          3. 当开始某些宏定义后需要用户实现代码的函数内部有#err提示,完成函数后请删除该#err
 */


/******************************************************************************
                                移植须知:
1:MCU必须在while中直接调用mcu_api.c内的wifi_uart_service()函数
2:程序正常初始化完成后,建议不进行关串口中断,如必须关中断,关中断时间必须短,关中断会引起串口数据包丢失
3:请勿在中断/定时器中断内调用上报函数
******************************************************************************/

#include "wifi.h"
#include "ulog.h"

#define DBG_TAG "wifi-decoder"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

/******************************************************************************
                              第一步:初始化
1:在需要使用到wifi相关文件的文件中include "wifi.h"
2:在MCU初始化中调用mcu_api.c文件中的wifi_protocol_init()函数
3:将MCU串口单字节发送函数填入protocol.c文件中uart_transmit_output函数内,并删除#error
4:在MCU串口接收函数中调用mcu_api.c文件内的uart_receive_input函数,并将接收到的字节作为参数传入
5:单片机进入while循环后调用mcu_api.c文件内的wifi_uart_service()函数
******************************************************************************/

#ifdef WEATHER_ENABLE
/**
 * @var    weather_choose
 * @brief  天气数据参数选择数组
 * @note   用户可以自定义需要的参数，注释或者取消注释即可，注意更改
 */
const char *weather_choose[WEATHER_CHOOSE_CNT] = {
    "temp",
    "humidity",
    "condition",
    "pm25",
    /*"pressure",
    "realFeel",
    "uvi",
    "tips",
    "windDir",
    "windLevel",
    "windSpeed",
    "sunRise",
    "sunSet",
    "aqi",
    "so2 ",
    "rank",
    "pm10",
    "o3",
    "no2",
    "co",*/
};
#endif

/******************************************************************************
                        1:dp数据点序列类型对照表
          **此为自动生成代码,如在开发平台有相关修改请重新下载MCU_SDK**
******************************************************************************/
const DOWNLOAD_CMD_S download_cmd[] =
{
  {DPID_FAIL_STATE, DP_TYPE_FAULT},
  {DPID_DEVICE_ID, DP_TYPE_VALUE},
  {DPID_VALVE_STATE, DP_TYPE_BOOL},
};



/******************************************************************************
                           2:串口单字节发送函数
请将MCU串口发送函数填入该函数内,并将接收到的数据作为参数传入串口发送函数
******************************************************************************/

/**
 * @brief  串口发送数据
 * @param[in] {value} 串口要发送的1字节数据
 * @return Null
 */
void uart_transmit_output(unsigned char value)
{
    //#error "请将MCU串口发送函数填入该函数,并删除该行"
    extern void WiFi_Byte_Send(uint8_t data);
    WiFi_Byte_Send(value);
    
/*
    //示例:
    extern void Uart_PutChar(unsigned char value);
    Uart_PutChar(value);	                                //串口发送函数
*/
}
/******************************************************************************
                           第二步:实现具体用户函数
1:APP下发数据处理
2:数据上报处理
******************************************************************************/

/******************************************************************************
                            1:所有数据上报处理
当前函数处理全部数据上报(包括可下发/可上报和只上报)
  需要用户按照实际情况实现:
  1:需要实现可下发/可上报数据点上报
  2:需要实现只上报数据点上报
此函数为MCU内部必须调用
用户也可调用此函数实现全部数据上报
******************************************************************************/

/**
 * @brief  系统所有dp点信息上传,实现APP和muc数据同步
 * @param  Null
 * @return Null
 * @note   此函数SDK内部需调用，MCU必须实现该函数内数据上报功能，包括只上报和可上报可下发型数据
 */
void all_data_update(void)
{
    //#error "请在此处理可下发可上报数据及只上报数据示例,处理完成后删除该行"
    //请根据dpid按照实际数据修改每个可下发可上报函数和只上报函数，并且要根据子设备id把子设备和网关本身的状态全部都上报上去
    //子设备id为"0000"，表示网关本身

    /*
    例如：
    网关本身dp：
    mcu_dp_bool_update(DPID_SWITCH,当前总开关,STR_GATEWAY_ITSELF_ID,my_strlen(STR_GATEWAY_ITSELF_ID)); //BOOL型数据上报;
    子设备dp：
    mcu_dp_bool_update(DPID_SWITCH_SPRAY,当前喷雾开关,子设备id,子设备id长度); //BOOL型数据上报;
    mcu_dp_enum_update(DPID_MODE,当前喷雾模式,子设备id,子设备id长度); //枚举型数据上报;
    mcu_dp_enum_update(DPID_COUNTDOWN_SET,当前喷雾倒计时,子设备id,子设备id长度); //枚举型数据上报;
    */
  
/* 
    //此代码为平台自动生成，请按照实际数据修改每个可下发可上报函数和只上报函数
    mcu_dp_fault_update(DPID_FAIL_STATE,当前故障状态,子设备ID,子设备ID长度); //故障型数据上报;
    mcu_dp_value_update(DPID_DEVICE_ID,当前故障设备ID,子设备ID,子设备ID长度); //VALUE型数据上报;
    mcu_dp_bool_update(DPID_VALVE_STATE,当前阀门状态,子设备ID,子设备ID长度); //BOOL型数据上报;

*/

}

/******************************************************************************
                                WARNING!!!    
                            2:所有数据上报处理
自动化代码模板函数,具体请用户自行实现数据处理
******************************************************************************/
/*****************************************************************************
函数名称 : dp_download_valve_state_handle
功能描述 : 针对DPID_VALVE_STATE的处理函数
输入参数 : value:数据源数据
        : length:数据长度
        : sub_id_buf:子设备id
        : sub_id_len:子设备id数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_valve_state_handle(const unsigned char value[], unsigned short length, unsigned char *sub_id_buf, unsigned char sub_id_len)
{
    //示例:当前DP类型为BOOL
    unsigned char ret;
    //0:关/1:开
    unsigned char valve_state;
    
    valve_state = mcu_get_dp_download_bool(value,length);
    if(valve_state == 0) {
        //开关关
        /*****************************************************************************
        //dp数据处理前需要判断是哪一个子设备id的dp
        //例如用户的网关下面有两个子设备id，一个是"1234"另一个是"5678"
        if(my_strcmp(sub_id_buf,"1234") == 0) {
    
        }else if(my_strcmp(sub_id_buf,"5678") == 0) {
    
        }
    
        //若子设备id是“0000”，则表示网关本身的dp
        *****************************************************************************/
  
    }else {
        //开关开
    }
  
    //处理完DP数据后应有反馈
    ret = mcu_dp_bool_update(DPID_VALVE_STATE,valve_state, sub_id_buf, sub_id_len);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}




/******************************************************************************
                                WARNING!!!                     
此部分函数用户请勿修改!!
******************************************************************************/

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
unsigned char dp_download_handle(unsigned char dpid,const unsigned char value[], unsigned short length,unsigned char* sub_id_buf,unsigned char sub_id_len)
{
    /****************************************************************
    当前函数处理可下发/可上报数据调用,具体函数内需要实现下发数据处理
    完成用需要将处理结果反馈至APP端,否则APP会认为下发失败
    请在该函数根据子设备的id自行实现子设备的dpid处理
    ****************************************************************/
    unsigned char ret;
    switch(dpid) {
        case DPID_VALVE_STATE:
            //阀门状态处理函数
            LOG_D("Got Downlink With Valve\r\n");
            ret = dp_download_valve_state_handle(value,length,sub_id_buf,sub_id_len);
        break;

        default:
        break;
    }
    return ret;
}

/**
 * @brief  获取所有dp命令总和
 * @param[in] Null
 * @return 下发命令总和
 * @note   该函数用户不能修改
 */
unsigned char get_download_cmd_total(void)
{
    return(sizeof(download_cmd) / sizeof(download_cmd[0]));
}


/******************************************************************************
                                WARNING!!!                     
此代码为SDK内部调用,请按照实际dp数据实现函数内部数据
******************************************************************************/

/**
 * @brief  wifi模块是否接收子设备入网请求结果通知（子设备是否实
           际入网成功需要查看ADD_DEV_RESULT_CMD命令字相关的命令）
 * @param[in] {result} 模块是否接收子设备入网请求结果;0:接收请求/1:拒绝请求
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void subdevice_add_result(unsigned char result)
{
    //#error "请自行实现子设备添加成功/失败代码,完成后请删除该行"
    //注意：此处结果只是wifi模块是否接收子设备的入网请求，子设备实际是否入网成功需要
    //查看ADD_DEV_RESULT_CMD宏（返回添加设备结果）所对应的结果
    if(result == 0) {
        //wifi模块接收子设备入网请求
    }else {
        //wifi模块拒绝子设备入网请求
    }
}

/**
 * @brief  wifi模块发送关闭入网指令给网关,此函数内获取需要删除
           的子设备id和子设备key，用户需要根据这两条信息自行删除子设备
 * @param[in] {data_buf} 接收到的data部分的首地址
 * @param[in] {data_len} 接收到的data部分的长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void subdevice_delete(unsigned char* data_buf,unsigned short data_len)
{
    //#error "请自行实现子设备删除成功/失败代码,完成后请删除该行"
    cJSON *root = NULL,*item = NULL;
    
    char* sub_id = NULL;  //子设备id
    char* devkey = NULL;  //子设备key
    unsigned char tp = NULL;  //移除类型
    
    unsigned char pstr[data_len + 1];
    my_memset(pstr, 0x00, data_len+1);
    my_memcpy(pstr, data_buf, data_len);

    root = cJSON_Parse(pstr);
    if(NULL == root){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT_ERR;
    }

    item = cJSON_GetObjectItem(root, "sub_id");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT_ERR;
    }
    sub_id = item->valuestring;

    item = cJSON_GetObjectItem(root, "devkey");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT_ERR;
    }
    devkey = item->valuestring;
    
    item = cJSON_GetObjectItem(root, "tp");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT_ERR;
    }
    tp = item->valueint;

    ///////////////请在此处根据获取到的相关数据删除对应的子设备/////////////////
    //sub_id: 子设备id
    //devkey: 子设备key
    //tp: 移除类型  0:移除子设备  1:APP恢复出厂设置
    
    
    
    cJSON_Delete(root);
    return;
    
EXIT_ERR:
    if(NULL != root) {
        cJSON_Delete(root);
    }
}

/**
 * @brief  wifi模块WIFI 模组定时（1-3 分钟）检测子设备在线状态
 * @param[in] {data_buf} 接收到的data部分的首地址
 * @param[in] {data_len} 接收到的data部分的长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void heart_beat_check(unsigned char* data_buf,unsigned short data_len)
{
    cJSON *root = NULL,*item = NULL;
    char* sub_id = NULL;          //需要检测心跳的子设备id
    
    unsigned char pstr[data_len + 1];
    my_memset(pstr, 0x00, data_len+1);
    my_memcpy(pstr, data_buf, data_len);

    root = cJSON_Parse(pstr);
    if(NULL == root){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT_ERR;
    }

    item = cJSON_GetObjectItem(root, "sub_id");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT_ERR;
    }
    
    sub_id = item->valuestring;
    
    //#error "请自行实现心跳检测代码,完成后请删除该行"
    /////////////////////////请在此处根据获取到的sub_id进行子设备心跳的回复////////////////////////
    //////////////////在线的设备需要回复心跳，连续2  个心跳周期不回复则认为该设备离线////////////////
    //这边只给出示例，具体用法请在mcu_api.c里面的heart_beat_report查看函数说明
    //heart_beat_report(sub_id, lowpower_flag);

    cJSON_Delete(root);
    return;
    
EXIT_ERR:
    if(NULL != root) {
        cJSON_Delete(root);
    }
}

#ifdef GROUP_SUBDEV_ENABLE
/**
 * @brief  群组子设备加入
 * @param[in] {data_buf} 接收到的data部分的首地址
 * @param[in] {data_len} 接收到的data部分的长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void group_subdev_add(unsigned char *data_buf, unsigned short data_len)
{
    #error "请自行实现群组子设备加入代码,完成后请删除该行"
    cJSON *root = NULL,*item = NULL,*cids_arr = NULL;
    unsigned int i = 0,cids_arr_sz = 0, send_cids_arr_sz = 0;
    
    char* gid = NULL;  //群组id
    char** cids = NULL;  //要加入群组的子设备集合
    unsigned char *rets = NULL;  //返回结果
    
    char pstr[data_len + 1];
    my_memset(pstr, 0x00, data_len+1);
    my_memcpy(pstr, data_buf, data_len);

    root = cJSON_Parse(pstr);
    if(NULL == root){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT1;
    }

    item = cJSON_GetObjectItem(root, "gid");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT1;
    }
    gid = item->valuestring;

    item = cJSON_GetObjectItem(root, "cids");
    
    if(NULL == item){
        //可在此添加错误提示信息，如：printf("xxx");
        goto EXIT1;
    }
    
    cids_arr    = item;
    cids_arr_sz = cJSON_GetArraySize(cids_arr);
    send_cids_arr_sz = cids_arr_sz;
    
    cids = (char**) malloc(sizeof(char *) * cids_arr_sz);
    if(NULL == cids) {
        //可在此添加错误提示信息，如：printf("xxx");
        goto EXIT1;
    }
    
    for(i=0; i<cids_arr_sz; i++){
        item = cJSON_GetArrayItem(cids_arr, i);
        if(NULL == item){
            //可在此添加错误提示信息，如：printf("xxx");
            continue;
        }
        cids[i] = item->valuestring;
    }
    
    rets = (unsigned char*) malloc(cids_arr_sz); 

    //************************************************************************************
    //请在此处根据获取到的群组id(gid)和要加入群组的子设备集合(cids)加入对应的子设备,
    //并将结果放入rets中。例如cids["12","34","56"]，如果“12”对应的子设备添加成功，“34”对应的子设备超过群组数上限，“56”对应的子设备超时;则rets填充为rets[0,1,2];
    //请将群组id以及添加成功的子设备id进行记录缓存添加，以便于对群组控制的其他操作（如：控制群组指令下发）
      
      
      
      
    //************************************************************************************
    char* out = NULL;
    unsigned char length = 0;
    cJSON *send_root = NULL, *send_arr_cids_item = NULL, *send_arr_rets_item = NULL;
     
    send_root = cJSON_CreateObject();
    if(NULL == send_root) {
        //可在此添加错误提示信息，如：printf("xxx");
        goto EXIT2;
    }
    
    cJSON_AddStringToObject(send_root, "gid", gid);
    
    send_arr_cids_item = cJSON_CreateArray();
    if(NULL == send_arr_cids_item){
        //可在此添加错误提示信息，如：printf("xxx");
        goto EXIT2;
    }
    for(i = 0;i < send_cids_arr_sz;i++) {
        cJSON_AddItemToArray(send_arr_cids_item, cJSON_CreateString(cids[i]));
    }
    cJSON_AddItemToObject(send_root, "cids", send_arr_cids_item);
    
    send_arr_rets_item = cJSON_CreateArray();
    if(NULL == send_arr_rets_item){
        //可在此添加错误提示信息，如：printf("xxx");
        goto EXIT2;
    }
    for(i = 0;i < send_cids_arr_sz;i++) {
        cJSON_AddItemToArray(send_arr_rets_item, cJSON_CreateNumber(rets[i]));
    }
    cJSON_AddItemToObject(send_root, "rets", send_arr_rets_item);

    out = cJSON_PrintUnformatted(send_root);
    
    if(NULL == out) {
        //可在此添加错误提示信息，如：printf("xxx");
        goto EXIT2;
    }
    
    length = set_wifi_uart_buffer(length, out, my_strlen(out));

    wifi_uart_write_frame(GROUP_SUBDEV_ADD_CMD, MCU_TX_VER, length);

EXIT2:
    free(out);
    cJSON_Delete(send_root);
    
EXIT1:
    free(cids);
    free(rets);
    cJSON_Delete(root);
    return;
}

/**
 * @brief  群组子设备删除
 * @param[in] {data_buf} 接收到的data部分的首地址
 * @param[in] {data_len} 接收到的data部分的长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void group_subdev_del(unsigned char *data_buf, unsigned short data_len)
{
    #error "请自行实现群组子设备删除代码,完成后请删除该行"
    cJSON *root = NULL,*item = NULL,*cids_arr = NULL;
    unsigned int i = 0,cids_arr_sz = 0, send_cids_arr_sz = 0;
      
    char* gid = NULL;  //群组id
    char** cids = NULL;  //要删除群组的子设备集合
    unsigned char *rets = NULL;  //返回结果
    
    char pstr[data_len + 1];
    my_memset(pstr, 0x00, data_len+1);
    my_memcpy(pstr, data_buf, data_len);

    root = cJSON_Parse(pstr);
    if(NULL == root){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT1;
    }

    item = cJSON_GetObjectItem(root, "gid");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT1;
    }
    gid = item->valuestring;

    item = cJSON_GetObjectItem(root, "cids");
    
    if(NULL == item){
        //可在此添加错误提示信息，如：printf("xxx");
        goto EXIT1;
    }
    
    cids_arr    = item;
    cids_arr_sz = cJSON_GetArraySize(cids_arr);
    send_cids_arr_sz = cids_arr_sz;
    
    cids = (char**) malloc(sizeof(char *) * cids_arr_sz);
    if(NULL == cids) {
        //可在此添加错误提示信息，如：printf("xxx");
        goto EXIT1;
    }
    
    for(i=0; i<cids_arr_sz; i++){
        item = cJSON_GetArrayItem(cids_arr, i);
        if(NULL == item){
            //可在此添加错误提示信息，如：printf("xxx");
            continue;
        }
        cids[i] = item->valuestring;
    }
    
    rets = (unsigned char*) malloc(cids_arr_sz); 

    //************************************************************************************
    //请在此处根据获取到的群组id(gid)和要删除群组的子设备集合(cids)删除对应的子设备,
    //并将结果放入rets中。例如cids["12","34","56"]，如果“12”对应的子设备删除成功，“34”对应的子设备超过群组数上限，“56”对应的子设备超时;则rets填充为rets[0,1,2];
    //请将群组id以及删除成功的子设备id进行记录缓存删除，以便于对群组控制的其他操作（如：控制群组指令下发）
      
      
      
      
    //************************************************************************************
    char* out = NULL;
    unsigned char length = 0;
    cJSON *send_root = NULL, *send_arr_cids_item = NULL, *send_arr_rets_item = NULL;
     
    send_root = cJSON_CreateObject();
    if(NULL == send_root) {
        //可在此添加错误提示信息，如：printf("xxx");
        goto EXIT2;
    }
    
    cJSON_AddStringToObject(send_root, "gid", gid);
    
    send_arr_cids_item = cJSON_CreateArray();
    if(NULL == send_arr_cids_item){
        //可在此添加错误提示信息，如：printf("xxx");
        goto EXIT2;
    }
    for(i = 0;i < send_cids_arr_sz;i++) {
        cJSON_AddItemToArray(send_arr_cids_item, cJSON_CreateString(cids[i]));
    }
    cJSON_AddItemToObject(send_root, "cids", send_arr_cids_item);
    
    send_arr_rets_item = cJSON_CreateArray();
    if(NULL == send_arr_rets_item){
        //可在此添加错误提示信息，如：printf("xxx");
        goto EXIT2;
    }
    for(i = 0;i < send_cids_arr_sz;i++) {
        cJSON_AddItemToArray(send_arr_rets_item, cJSON_CreateNumber(rets[i]));
    }
    cJSON_AddItemToObject(send_root, "rets", send_arr_rets_item);

    out = cJSON_PrintUnformatted(send_root);
    
    if(NULL == out) {
        //可在此添加错误提示信息，如：printf("xxx");
        goto EXIT2;
    }
    
    length = set_wifi_uart_buffer(length, out, my_strlen(out));

    wifi_uart_write_frame(GROUP_SUBDEV_DEL_CMD, MCU_TX_VER, length);

EXIT2:
    free(out);
    cJSON_Delete(send_root);
    
EXIT1:
    free(cids);
    free(rets);
    cJSON_Delete(root);
    return;
}
#endif 

#ifdef SUPPORT_GREEN_TIME
/**
 * @brief  获取到的格林时间
 * @param[in] {time} 获取到的格林时间数据
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_get_greentime(unsigned char time[])
{
    #error "请自行完成格林时间写入代码,并删除该行"
    /*
    time[0]为是否获取时间成功标志，为 0 表示失败，为 1表示成功
    time[1] 为 年 份 , 0x00 表 示2000 年
    time[2]为月份，从 1 开始到12 结束
    time[3]为日期，从 1 开始到31 结束
    time[4]为时钟，从 0 开始到23 结束
    time[5]为分钟，从 0 开始到59 结束
    time[6]为秒钟，从 0 开始到59 结束
    */
    if(time[0] == 1) {
        //正确接收到wifi模块返回的格林数据
    }else {
        //获取格林时间出错,有可能是当前wifi模块未联网
    }
}
#endif

#ifdef SUPPORT_MCU_RTC_CHECK
/**
 * @brief  MCU校对本地RTC时钟
 * @param[in] {time} 获取到的本地时间数据
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_write_rtctime(unsigned char time[])
{
    #error "请自行完成RTC时钟写入代码,并删除该行"
    /*
    time[0]为是否获取时间成功标志，为 0 表示失败，为 1表示成功
    time[1] 为 年 份 , 0x00 表 示2000 年
    time[2]为月份，从 1 开始到12 结束
    time[3]为日期，从 1 开始到31 结束
    time[4]为时钟，从 0 开始到23 结束
    time[5]为分钟，从 0 开始到59 结束
    time[6]为秒钟，从 0 开始到59 结束
    time[7]为星期，从 1 开始到 7 结束，1代表星期一
    */
    if(time[0] == 1) {
        //正确接收到wifi模块返回的本地时钟数据
    }else {
        //获取本地时钟数据出错,有可能是当前wifi模块未联网
    }
}
#endif

#ifdef BATCH_ADD_DEV_ENABLE
/**
 * @brief  批量添加同一个pid的多个子设备请求结果通知
 * @param[in] {result} 模块是否接收子设备添加请求结果;0:接收请求/1:拒绝请求
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void batch_add_dev_result(unsigned char result)
{
    #error "请自行实现批量添加同一个pid的多个子设备请求结果处理,完成后请删除该行"
    if(result == 0) {
        //批量添加子设备数据接收成功
    }else {
        //批量添加子设备数据接收失败
    }
}

/**
 * @brief  批量添加设备添加结果处理
 * @param[in] {cids} 子设备集合
 * @param[in] {rets} 0成功，非0失败
 * @param[in] {keys} 秘钥，仅单点设备使用，其他为NULL
 * @param[in] {num} 子设备的数量
 * @return Null
 * @note   MCU需要自行实现该功能
 */
static void user_add_result_deal(char* cids[], char* rets, char* keys[], char num)
{
    #error "请自行实现设备添加结果代码,完成后请删除该行"

    //例如cids["12","34","56"],rets[0,0,1],
    //代表“12”对应的子设备添加成功 “34”对应的子设备添加成功 “56”对应的子设备添加失败
    //keys["XXXX","XXX","XXX"]表示密钥(目前仅单点设备有这个字段，其他设备该字段可忽略)
    
    
    
}

/**
 * @brief  批量添加设备添加结果
 * @param[in] {data_buf} 接收到的data部分的首地址
 * @param[in] {data_len} 接收到的data部分的长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void add_dev_result_get(unsigned char* data_buf,unsigned short data_len)
{
    #error "请自行实现设备添加结果代码,完成后请删除该行"
    cJSON *root = NULL, *item = NULL, *cid_arr = NULL, *rets_arr = NULL, *key_arr = NULL;
    unsigned int arr_sz = 0, i = 0;
    /////////////////////////////////////////////////
    char** cids = NULL;  //要加入群组的子设备集合(sub_id集合)
    char* rets = NULL;
    char** keys = NULL;  //秘钥
    
    unsigned char pstr[data_len + 1];
    my_memset(pstr, 0x00, data_len+1);
    my_memcpy(pstr, data_buf, data_len);

    root = cJSON_Parse(pstr);
    if(NULL == root){
        //可在此添加提示信息，如：printf("xxx");
        goto ADD_SUB_ERR;
    }
      
    item = cJSON_GetObjectItem(root, "cids");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto ADD_SUB_ERR;
    }
    
    cid_arr = item;
    arr_sz = cJSON_GetArraySize(cid_arr);
    
    cids = (char**) malloc(sizeof(char *) * arr_sz);
    if(NULL == cids) {
        //可在此添加提示信息，如：printf("xxx");
        return;
    }
    
    for(i=0; i<arr_sz; i++){
        item = cJSON_GetArrayItem(cid_arr, i);
        if(NULL == item){
            //可在此添加提示信息，如：printf("xxx");
            continue;
        }
        cids[i] = item->valuestring;
    }
    
    item = cJSON_GetObjectItem(root, "rets");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto ADD_SUB_ERR;
    }
    
    rets_arr = item;
    if(arr_sz != cJSON_GetArraySize(rets_arr))
    {
        //可在此添加提示信息，如：printf("xxx");
        return;
    }
    
    rets = (char*)malloc(sizeof(arr_sz));
    if(NULL == rets) {
        //可在此添加提示信息，如：printf("xxx");
        return;
    }
    
    for(i=0; i<arr_sz; i++){
        item = cJSON_GetArrayItem(rets_arr, i);
        if(NULL == item){
            //可在此添加提示信息，如：printf("xxx");
            continue;
        }
        rets[i] = item->valueint;
    }
    
    #error "如果有单点设备,请打开此段注释,完善相关逻辑,完成后请删除该行"
    /*
    item = cJSON_GetObjectItem(root, "key");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto ADD_SUB_ERR;
    }
    
    key_arr = item;
    if(arr_sz != cJSON_GetArraySize(key_arr))
    {
        //可在此添加提示信息，如：printf("xxx");
        return;
    }
    
    keys = (char**) malloc(sizeof(char *) * arr_sz);
    if(NULL == keys) {
        //可在此添加提示信息，如：printf("xxx");
        return;
    }
    
    for(i=0; i<arr_sz; i++){
        item = cJSON_GetArrayItem(key_arr, i);
        if(NULL == item){
            //可在此添加提示信息，如：printf("xxx");
            continue;
        }
        keys[i] = item->valuestring;
    }
    */
    
    /////////////////////////////用户需要在此进行批量添加设备添加结果的处理/////////////////////////////////
    user_add_result_deal(cids, rets, keys, arr_sz);

    ////////////////////////////////用户需要在此进行设备添加结果的处理//////////////////////////////////
    wifi_uart_write_frame(ADD_DEV_RESULT_CMD, MCU_TX_VER, 0);

    free(rets);
    free(cids);
    cJSON_Delete(root);
    return;
    
ADD_SUB_ERR:
    if(NULL != root) {
        cJSON_Delete(root);
    }
}
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
unsigned char ctrl_group_issued(const unsigned char value[],const unsigned char group_id_buf[],unsigned short group_id_len)
{
    //这边是数据下发函数，请根据实际情况调用
    unsigned char dp_id,index;
    unsigned char dp_type;
    unsigned char ret = 0;
    unsigned short dp_len;
    
    dp_id = value[0];
    dp_type = value[1];
    dp_len = (value[2] <<8) + value[3];
    
    index = get_dowmload_dpid_index(dp_id);
    if(dp_type != download_cmd[index].dp_type) {
        //错误提示,无此dp
        return ERROR;
    }
    
    #error "请自行实现控制群组指令下发代码,完成后请删除该行"
    
    //此处由用户完成群组dp处理函数
    
    /************************以下给出demo，仅供参考*****************************************
    //在此以现有两个群组为例，群组id为"01"和"02"
    //"01"群组中有2个子设备，子设备id分别为"11"、"12"
    //"02"群组中有3个子设备，子设备id分别为"21"、"22"、"23"
    
    if(0 == my_strcmp(group_id_buf, "01")) {
        ret = dp_download_handle(dp_id, value + 4, dp_len, "11", my_strlen("11"));
        ret = dp_download_handle(dp_id, value + 4, dp_len, "12", my_strlen("12"));
    
    }else if(0 == my_strcmp(group_id_buf, "02")) {
        ret = dp_download_handle(dp_id, value + 4, dp_len, "21", my_strlen("21"));
        ret = dp_download_handle(dp_id, value + 4, dp_len, "22", my_strlen("22"));
        ret = dp_download_handle(dp_id, value + 4, dp_len, "23", my_strlen("23"));
    }
    *****************************************************************************************/
    
    
    return ret;
}
#endif

#ifdef WIFI_TEST_ENABLE
/**
 * @brief  wifi功能测试反馈
 * @param[in] {result} wifi功能测试结果;0:失败/1:成功
 * @param[in] {rssi} 测试成功表示wifi信号强度/测试失败表示错误类型
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void wifi_test_result(unsigned char result,unsigned char rssi)
{
    //#error "请自行实现wifi功能测试成功/失败代码,完成后请删除该行"
    if(result == 0) {
        //测试失败
        if(rssi == 0x00) {
            //未扫描到名称为tuya_mdev_test路由器,请检查
        }else if(rssi == 0x01) {
            //模块未授权
        }
    }else {
        //测试成功
        //rssi为信号强度(0-100, 0信号最差，100信号最强)
    }
}
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
void wifi_status_result(unsigned char result)
{
    #error "请自行实现WIFI 工作状态结果代码,完成后请删除该行"
    switch(result) {
        case 0:
            //wifi工作状态1
        break;
        case 1:
            //wifi工作状态2
        break;
        case 2:
            //wifi工作状态3
        break;
        case 3:
            //wifi工作状态4
        break;
        case 4:
            //wifi工作状态5
        break;
        case 5:
            //wifi工作状态6
        break;
        case 6:
            //wifi工作状态7
        break;
        default:
        break;
    }
}
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
void inform_dev_del_status(unsigned char result)
{
    #error "请自行实现恢复出厂设置代码,完成后请删除该行"
    switch(result) {
        case 0:
            //本地恢复出厂
        break;
        case 1:
            //远程移除
        break;
        case 2:
            //本地移除
        break;
        case 3:
            //远程恢复出厂
        break;
        case 4:
            //清除数据，但是网关不离网
        break;
        default:
        break;
    }
}
#endif

#ifdef LOCAL_SUBDEV_DEL_ENABLE
/**
 * @brief  本地删除子设备结果
 * @param[in] {result} 本地子设备删除结果结果;0:成功/1:失败
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void local_del_subdev(unsigned char result)
{
    #error "请自行实现wifi功能测试成功/失败代码,完成后请删除该行"
    if(result == 0) {
        //测试成功
    }else {
        //测试失败
    }
}
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
void local_subdev_limit(unsigned char result)
{
    #error "请自行实现本地允许/关闭添加子设备结果通知代码,完成后请删除该行"
    if(result == 0) {
        //本地允许/关闭添加子设备成功
    }else {
        //本地允许/关闭添加子设备失败
    }
}
#endif

#ifdef GET_MODULE_REMAIN_MEMORY_ENABLE
/**
 * @brief  获取模块内存
 * @param[in] {module_memory} 获取模块内存的大小
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void remain_memory_result(unsigned int module_memory)
{
    #error "请自行实现获取模块内存处理代码,完成后请删除该行"
    
}
#endif

#ifdef QUR_SUBDEV_LIST_ENABLE
/**
 * @brief  子设备列表
 * @param[in] {subdev_list_buf} 存放子设备的buf
 * @param[in] {buf_len} 子设备buf的长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void local_subdev_list(unsigned char *subdev_list_buf,unsigned short buf_len)
{
    unsigned char next_package_flag;
    unsigned char package_idx;
    unsigned char sub_node_num;
    unsigned char offset = 2;
    unsigned char sub_id_len;//包长度
    unsigned char i;
    tSUB_NODE *sub_node = NULL; //这个里面存放的就是
    
    next_package_flag = (subdev_list_buf[0] >> 7) & 0x01;
    package_idx = subdev_list_buf[0] & 0x7F;
    sub_node_num = subdev_list_buf[1];
    
    sub_node = (tSUB_NODE*)malloc(sizeof(tSUB_NODE) * sub_node_num);
    if(NULL == sub_node) {
        //可在此添加提示信息，如：printf("xxx");
        return;
    }
    my_memset(sub_node, 0, sizeof(tSUB_NODE) * sub_node_num);
    
    for(i = 0,offset = 2;i < sub_node_num;i++) {
        my_memcpy(&sub_node[i], subdev_list_buf + offset, subdev_list_buf[offset] + 1);
        offset += subdev_list_buf[offset] + 1; //偏移到下一个节点的位置
    }
    
    #error "请自行实现子设备列表代码,完成后请删除该行"
    if(next_package_flag == FALSE) { //代表后续以及没有包了，结束发送
        //当前包序号为package_idx
        //用户自行处理 sub_node 中的子设备信息
        
    }else { //后续还有包，下次还会调用该函数
        //包序号为package_idx
        //用户自行处理 sub_node 中的子设备信息
        
    }

    free(sub_node);
}
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
void upgrade_package_choose(unsigned char package_sz)
{
    unsigned short length = 0;
    length = set_wifi_uart_byte(length,package_sz);
    wifi_uart_write_frame(UPDATE_START_CMD, MCU_TX_VER, length);
}

/**
 * @brief  网关本身MCU升级包传输
 * @param[in] {value} 固件数据缓冲区
 * @param[in] {position} 当前数据包在于固件位置
 * @param[in] {length} 当前固件包长度(固件包长度为0时,表示固件包发送完成)
 * @return 成功/失败
 * @note   MCU需要自行实现该功能
 */
unsigned char mcu_firm_update_handle(const unsigned char value[],unsigned long position,unsigned short length)
{
    #error "请自行完成MCU固件升级代码,完成后请删除该行"
    if(length == 0) {
        //固件数据发送完成
    }else {
        //固件数据处理
    }
    
    return SUCCESS;
}

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
void subdev_upgrade_package_choose(unsigned char package_sz,unsigned char*sub_dev_id,unsigned char sub_dev_len)
{
    #error "请自行实现子设备升级代码,完成后请删除该行"
    ////////////此次升级是针对对应的子设备的，子设备处理用户自行实现/////////////////
    
    unsigned short length = 0;
    length = set_wifi_uart_byte(length,package_sz);
    wifi_uart_write_frame(SUBDEV_START_UPGRADE_CMD, MCU_TX_VER, length);
}

/**
 * @brief  子设备MCU升级包大小选择
 * @param[in] {sub_id_buf} 子设备id
 * @param[in] {value} 固件数据缓冲区
 * @param[in] {position} 当前数据包在于固件位置
 * @param[in] {length} 当前固件包长度(固件包长度为0时,表示固件包发送完成)
 * @return 成功/失败
 * @note   MCU需要自行实现该功能
 */
unsigned char subdev_firm_update_handle(unsigned char *sub_id_buf,const unsigned char value[],unsigned long position,unsigned short length)
{
    #error "请自行完成MCU固件升级代码,完成后请删除该行"
    if(length == 0) {
        //固件数据发送完成
    }else {
        //固件数据处理
    }
    
    return SUCCESS;
}

/**
 * @brief  查询子设备版本
 * @param[in] {mcu_ver} mcu版本
 * @param[in] {sub_id} 子设备id
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void qur_subdev_ver_report(unsigned char *sub_id,unsigned char *mcu_ver)
{
    unsigned short length = 0;
    
    cJSON *root = NULL;
    char* out = NULL;
    
    root = cJSON_CreateObject();
    if(NULL == root){
        //可在此添加提示信息，如：printf("xxx");
        return;
    }
    
    cJSON_AddStringToObject(root, "sub_id", sub_id);
    
    cJSON_AddStringToObject(root, "ver", mcu_ver);
    
    out = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    if(NULL == out){
        //可在此添加提示信息，如：printf("xxx");
        return;
    }
    
    length = set_wifi_uart_buffer(length, out, my_strlen(out));
    wifi_uart_write_frame(QUR_SUBDEV_VER_CMD, MCU_TX_VER, length);

    free(out);
}

/**
 * @brief  wifi模块查询子设备版本号
 * @param[in] {data_buf} 接收到的data部分的首地址
 * @param[in] {data_len} 接收到的data部分的长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void qur_subdev_ver_get(unsigned char* data_buf,unsigned short data_len)
{
    cJSON *root = NULL,*item = NULL;
    
    char* sub_id = NULL;  //需要检测心跳的子设备id
    
    unsigned char pstr[data_len + 1];
    my_memset(pstr, 0x00, data_len+1);
    my_memcpy(pstr, data_buf, data_len);

    root = cJSON_Parse(pstr);
    if(NULL == root){
        //可在此添加提示信息，如：printf("xxx");
        goto ADD_SUB_ERR;
    }

    item = cJSON_GetObjectItem(root, "sub_id");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto ADD_SUB_ERR;
    }
    sub_id = item->valuestring;
    
    #error "请自行实现wifi模块查询子设备版本号代码,完成后请删除该行"
    //请在此处填写子设备对应的mcu版本号
    /*
    例如mcu版本号为1.0.3
    qur_subdev_ver_report(sub_id,"1.0.3");
    */

    cJSON_Delete(root);
    return;
    
ADD_SUB_ERR:
    if(NULL != root) {
        cJSON_Delete(root);
    }
}
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
                                                                    const unsigned char sub_id_buf[], unsigned short sub_id_len)
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
        //错误提示,无此dp
        return ERROR;
    }
    
    #error "请自行实现控制群组指令下发代码,完成后请删除该行"
    
    //此处由用户完成群组dp处理函数,子设备id用户可根据实际需要自行使用
    
    /************************以下给出demo，仅供参考*****************************************
    //在此以现有两个群组为例，群组id为"01"和"02"
    //"01"群组中有2个子设备，子设备id分别为"11"、"12"
    //"02"群组中有3个子设备，子设备id分别为"21"、"22"、"23"
    
    if(0 == my_strcmp(group_id_buf, "01")) {
        ret = dp_download_handle(dp_id, value + 4, dp_len, "11", my_strlen("11"));
        ret = dp_download_handle(dp_id, value + 4, dp_len, "12", my_strlen("12"));
    }else if(0 == my_strcmp(group_id_buf, "02")) {
        ret = dp_download_handle(dp_id, value + 4, dp_len, "21", my_strlen("21"));
        ret = dp_download_handle(dp_id, value + 4, dp_len, "22", my_strlen("22"));
        ret = dp_download_handle(dp_id, value + 4, dp_len, "23", my_strlen("23"));
    }
    *****************************************************************************************/
    
    
    
    return ret;
}
#endif

#ifdef UART_CONFIG_INTEGRATED_ENABLE
/**
 * @brief  串口配网（一体式）结果处理
 * @param[in] {result} 模块返回结果
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void uart_config_intrgrated_result(unsigned char result)
{
    #error "请自行实现串口配网（一体式）结果处理代码,完成后请删除该行"
    switch(result) {
        case 0x00:
            //成功
        break;
        case 0x01:
            //不在配网状态
        break;
        case 0x02:
            //json数据非法
        break;
        default:
        break;
    }
}
#endif

#ifdef UART_CONFIG_DISTRIBUTED_ENABLE        //开启串口透传配网(分布式)
/**
 * @brief  WIFI发送广播包( 串口透传配网(分布式) )数据处理
 * @param[in] {p_data} 广播包数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void send_broad_packet(const unsigned char p_data[], unsigned short data_len)
{
    #error "请自行实现WIFI发送广播包( 串口透传配网(分布式) )数据处理代码,完成后请删除该行"
    unsigned short length = 0;
    unsigned char result[2] = {0};
    
    //请在此处添加广播包数据处理代码,并将处理结果写入result[0](0x00:成功/0x01:失败)和result[1](0x00:成功/其他:失败)
    
    
    length = set_wifi_uart_buffer(length, result, sizeof(result));
    wifi_uart_write_frame(SEND_BROAD_PACKET_CMD, MCU_TX_VER, length);
}

/**
 * @brief  WIFI上报配网信息( 串口透传配网(分布式) )
 * @param[in] {p_data} 加密数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void upload_config_infor(const unsigned char p_data[], unsigned short data_len)
{
    #error "请自行实现WIFI上报配网信息( 串口透传配网(分布式) )数据处理代码,完成后请删除该行"
    //请在此处添加上报的配网信息处理代码
    
    
    wifi_uart_write_frame(UPLOAD_CONFIG_INFOR_CMD, MCU_TX_VER, 0);
}

/**
 * @brief  wifi模块主动断开连接( 串口透传配网(分布式) )
 * @param  Null
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void wifi_disconnect(void)
{
    #error "请自行实现wifi模块主动断开连接( 串口透传配网(分布式) )处理代码,完成后请删除该行"
    //请在此处添加wifi模块主动断开连接处理代码
    
    
    wifi_uart_write_frame(WIFI_DISCONNECT_CMD, MCU_TX_VER, 0);
}
#endif

#ifdef GET_DP_STATE_ENABLE
/**
 * @brief  查询dp状态
 * @param[in] {p_data} 数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void get_dp_state(const unsigned char p_data[], unsigned short data_len)
{
    cJSON *root = NULL,*item = NULL;
    cJSON *dpid_arr = NULL;
    unsigned int i = 0,dpid_arr_sz = 0;
    
    char* p_sub_id = NULL;  //设备id
    char* p_dpid = NULL;   //dpid数组
    
    char pstr[data_len + 1];
    my_memset(pstr, 0x00, data_len+1);
    my_memcpy(pstr, p_data, data_len);

    root = cJSON_Parse(pstr);
    if(NULL == root){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT;
    }

    item = cJSON_GetObjectItem(root, "sub_id");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT;
    }
    p_sub_id = item->valuestring;

    item = cJSON_GetObjectItem(root, "dpid");
    
    if(NULL == item){
        //可在此添加错误提示信息，如：printf("xxx");
        goto EXIT;
    }
    
    dpid_arr    = item;
    dpid_arr_sz = cJSON_GetArraySize(dpid_arr);
    
    p_dpid = (char*) malloc(sizeof(unsigned char) * dpid_arr_sz);
    if(NULL == p_dpid) {
        //可在此添加错误提示信息，如：printf("xxx");
        goto EXIT;
    }
    
    for(i=0; i<dpid_arr_sz; i++){
        item = cJSON_GetArrayItem(dpid_arr, i);
        if(NULL == item){
            //可在此添加错误提示信息，如：printf("xxx");
            continue;
        }
        p_dpid[i] = item->valueint;
    }
    
    #error "请自行实现查询dp状态处理代码,完成后请删除该行"
    //请在此处添加查询dp状态处理代码, p_sub_id: 设备id    p_dpid: dpid数组
    
    
    //查询完成后需要上报，可以在 protocol.c 文件中的 all_data_update(void) 函数中找到对应dp上报函数进行上报
    

EXIT:
    free(p_dpid);
    cJSON_Delete(root);
    return;
}
#endif

#ifdef UPDATA_SUBDEV_ONLINE_STATE_ENABLE
/**
 * @brief  更新子设备在线/离线状态结果处理
 * @param[in] {result} 模块返回结果
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void updata_subden_online_state_result(unsigned char result)
{
    #error "请自行实现更新子设备在线/离线状态结果处理代码,完成后请删除该行"
    if(0 == result) {
        //成功
    }else {
        //失败
    }
}
#endif

#ifdef GET_MODULE_MAC_ENABLE
/**
 * @brief  获取模块的MAC地址结果处理
 * @param[in] {p_data} 数据
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void get_module_mac_result(const unsigned char p_data[])
{
    #error "请自行实现获取模块的MAC地址结果处理代码,完成后请删除该行"
    unsigned char result = 0;
    unsigned char mac[6] = {0};
    
    result = p_data[0];
    
    if(0x00 == result) {
        my_memcpy(mac, &p_data[1], sizeof(mac));
        //在此可对mac地址数据进行处理
    
    }else {
        //获取失败
    }
}
#endif

#ifdef RECORD_STATE_UPLOAD_RT_ENABLE
/**
 * @brief  记录型状态实时上报（带时间）结果处理
 * @param[in] {result} 模块返回结果
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void record_state_upload_rt_result(unsigned char result)
{
    #error "请自行实现记录型状态实时上报（带时间）结果处理代码,完成后请删除该行"
    if(0 == result) {
        //上报成功
    }else {
        //上报失败
    }
}
#endif

#ifdef QUERY_SUBDEV_BIND_STATE_ENABLE
/**
 * @brief  查询子设备绑定状态结果
 * @param[in] {p_data} 数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void query_subdev_bind_state_result(const unsigned char p_data[], unsigned short data_len)
{
    cJSON *root = NULL,*item = NULL;
    
    char* p_sub_id = NULL;  //子设备id
    int ret = 0;   //绑定状态
    
    char pstr[data_len + 1];
    my_memset(pstr, 0x00, data_len+1);
    my_memcpy(pstr, p_data, data_len);

    root = cJSON_Parse(pstr);
    if(NULL == root){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT;
    }

    item = cJSON_GetObjectItem(root, "sub_id");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT;
    }
    p_sub_id = item->valuestring;

    item = cJSON_GetObjectItem(root, "ret");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT;
    }
    ret = item->valueint;
    
    #error "请自行实现查询子设备绑定状态结果处理代码,完成后请删除该行"
    //请在此处添加查询子设备绑定状态结果处理代码,
    // p_sub_id: 设备id
    // ret: 绑定状态（3，4状态主要针对具有双链路功能的子设备， 普通设备不会返回这两个状态）
    //    0：和网关绑定成功
    //    1：网关中有记录但是未绑定（正在绑定中/云端没有该子设备记录）
    //    2：未绑定(未入网）
    //    3: 与手机绑定，但是未和网关绑定
    //    4：未和网关绑定，与手机绑定关系未知。
    


EXIT:
    cJSON_Delete(root);
}
#endif

#ifdef QUERY_GROUP_SUBDEV_ENABLE
/**
 * @brief  查询群组里的子设备结果
 * @param[in] {p_data} 数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void query_group_subdev_result(const unsigned char p_data[], unsigned short data_len)
{
    cJSON *root = NULL,*item = NULL;
    
    char* p_gid = NULL;  //群组id
    char* p_subid = NULL;  //子设备id

    
    char pstr[data_len + 1];
    my_memset(pstr, 0x00, data_len+1);
    my_memcpy(pstr, p_data, data_len);

    root = cJSON_Parse(pstr);
    if(NULL == root){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT;
    }

    item = cJSON_GetObjectItem(root, "gid");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT;
    }
    p_gid = item->valuestring;

    item = cJSON_GetObjectItem(root, "sub_id");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT;
    }
    p_subid = item->valuestring;
    
    #error "请自行实现查询群组里的子设备结果处理代码,完成后请删除该行"
    //请在此处添加查询群组里的子设备结果处理代码,
    // p_gid: 群组id
    // p_subid: 子设备id
    


EXIT:
    cJSON_Delete(root);
}
#endif

#ifdef UPLOAD_GROUP_LOCAL_CHANGE_ENABLE
/**
 * @brief  上报群组本地改变的dp结果
 * @param[in] {result} 模块返回结果
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void upload_group_local_change_dp_result(unsigned char result)
{
    #error "请自行实现上报群组本地改变的dp结果处理代码,完成后请删除该行"
    if(0 == result) {
        //成功
    }else {
        //失败
    }
}
#endif


#ifdef IR_CTRL_ENABLE
/**
 * @brief  红外控制码发送数据处理
 * @param[in] {p_data} 数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void ir_ctrl_cmd_send(const unsigned char p_data[], unsigned short data_len)
{
    unsigned char ret = 0;
    unsigned char length = 0;
    unsigned char sub_cmd = p_data[0];
    
    switch(sub_cmd) {
        case 0x00: {
            unsigned char ir_code_total = (p_data[1] >> 4) & 0xf;                       //当前有多少个码发送
            unsigned char ir_code_num = p_data[1] & 0xf;                                //当前是第几个码(从0开始)
            unsigned char repeat_time = p_data[2];                                      //针对特殊的码需要重复发送
            unsigned int freq = (p_data[3] << 24) | (p_data[4] << 16) | (p_data[5] << 8) | p_data[6]; //当前红外码的频率
            unsigned short ir_code_len = (p_data[7] << 8) | p_data[8];                  //当前红外码总长（以2个字节为一个单位）
            unsigned short ir_code_offset = (p_data[9] << 8) | p_data[10];              //针对长码需要发送时这里会使用偏移量通知（首包为0）
            const unsigned char *p_ir_code = &p_data[11];                               //红外码：以2个字节为一个单位
            
            #error "请自行实现红外控制码发送数据处理代码,完成后请删除该行"
            //根据处理结果，对ret赋值  成功:1  失败:2
            //ret = 1;   或者  ret = 2;
            
            
            
            length = set_wifi_uart_byte(length, sub_cmd);
            length = set_wifi_uart_byte(length, ret);
            
            wifi_uart_write_frame(IR_CTRL_CMD_SEND_CMD, MCU_TX_VER, length);
        }
        break;
        
        default:
        break;
    }
}

/**
 * @brief  红外控制码学习
 * @param[in] {p_data} 数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void ir_ctrl_cmd_learn(const unsigned char p_data[], unsigned short data_len)
{
    unsigned char length = 0;
    unsigned char sub_cmd = p_data[0];
    unsigned char time_out = p_data[1];
    
    switch(sub_cmd) {
        case 0x00: {
            
            
            unsigned int freq = 38000;              //当前红外码的频率（默认38kHz）
            unsigned short ir_code_len = 0;         //当前红外码总长（以2个字节为一个单位）
            unsigned short ir_code_offset = 0;      //针对长码需要发送时这里会使用偏移量通知（首包为0）
            const unsigned char *p_ir_code = NULL;    //红外码：以2个字节为一个单位
            
            #error "请自行实现红外控制码学习处理代码,完成后请删除该行"
            //请将红外码的相关数值赋值给对应的变量
            //频率赋值给freq  红外码总长赋值给ir_code_len  偏移量赋值给ir_code_offset  红外码缓存区赋值给p_ir_code
            
            
            
            length = set_wifi_uart_byte(length, sub_cmd);
            length = set_wifi_uart_byte(length, (freq >> 24) & 0xff);
            length = set_wifi_uart_byte(length, (freq >> 16) & 0xff);
            length = set_wifi_uart_byte(length, (freq >> 8) & 0xff);
            length = set_wifi_uart_byte(length, freq & 0xff);
            length = set_wifi_uart_byte(length, (ir_code_len >> 8) & 0xff);
            length = set_wifi_uart_byte(length, ir_code_len & 0xff);
            length = set_wifi_uart_byte(length, (ir_code_offset >> 8) & 0xff);
            length = set_wifi_uart_byte(length, ir_code_offset & 0xff);
            length = set_wifi_uart_buffer(length, p_ir_code, ir_code_len - ir_code_offset);
            
            wifi_uart_write_frame(IR_CTRL_CMD_LEARN_CMD, MCU_TX_VER, length);
        }
        break;
        
        default:
        break;
    }
}

/**
 * @brief  红外控制码取消学习
 * @param  Null
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void ir_ctrl_cmd_cancel_learn(void)
{
    #error "请自行实现红外控制码取消学习处理代码,完成后请删除该行"
    
    unsigned char ret = 0;
    unsigned char length = 0;
    
    //在此添加红外控制码取消学习处理
    //根据处理结果，对ret赋值  成功:1  失败:2
    //ret = 1;   或者  ret = 2;
    
    
    
    length = set_wifi_uart_byte(length, ret);
    
    wifi_uart_write_frame(IR_CTRL_CMD_CANCEL_LEARN_CMD, MCU_TX_VER, length);
}
#endif

#ifdef WEATHER_ENABLE
/**
* @brief  mcu打开天气服务
 * @param  Null
 * @return Null
 */
void mcu_open_weather(void)
{
    int i = 0;
    char buffer[20] = {0};
    unsigned char weather_len = 0;
    unsigned short send_len = 0;
    unsigned char weather_update_time_lag = 0;
    
    send_len = set_wifi_uart_byte(send_len, OPEN_WEATHER_SUBCMD);
    
    if(WEATHER_UPDATE_TIME_LAG <= 0) {
        weather_update_time_lag = 0;
    }else if(WEATHER_UPDATE_TIME_LAG >= 0xff) {
        weather_update_time_lag = 0xff;
    }else {
        weather_update_time_lag = WEATHER_UPDATE_TIME_LAG;
    }
    send_len = set_wifi_uart_byte(send_len, weather_update_time_lag);
    
    weather_len = sizeof(weather_choose) / sizeof(weather_choose[0]);
      
    for(i=0;i<weather_len;i++) {
        buffer[0] = sprintf(buffer+1,"w.%s",weather_choose[i]);
        send_len = set_wifi_uart_buffer(send_len, (unsigned char *)buffer, buffer[0]+1);
    }
    
    #error "请根据提示，自行完善天气服务配置，完成后请删除该行"
    /*
    //当获取的参数有和时间有关的参数时(如:日出日落)，需要搭配t.unix或者t.local使用，需要获取的参数数据是按照格林时间还是本地时间
    buffer[0] = sprintf(buffer+1,"t.unix"); //格林时间   或使用  buffer[0] = sprintf(buffer+1,"t.local"); //本地时间
    send_len = set_wifi_uart_buffer(send_len, (unsigned char *)buffer, buffer[0]+1);
    */
    
    buffer[0] = sprintf(buffer+1,"w.date.%d",WEATHER_FORECAST_DAYS_NUM);
    send_len = set_wifi_uart_buffer(send_len, (unsigned char *)buffer, buffer[0]+1);
    
    wifi_uart_write_frame(EXPAND_FUNC_CMD, MCU_TX_VER, send_len);
}

/**
 * @brief  打开天气功能返回用户自处理函数
 * @param[in] {res} 打开天气功能返回结果
 * @ref       0: 失败
 * @ref       1: 成功
 * @param[in] {err} 错误码
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void weather_open_return_handle(unsigned char res, unsigned char err)
{
    #error "请自行完成打开天气功能返回数据处理代码,完成后请删除该行"
    unsigned char err_num = 0;
    
    if(res == 1) {
        //打开天气返回成功
    }else if(res == 0) {
        //打开天气返回失败
        //获取错误码
        err_num = err; 
    }
}

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
void weather_data_user_handle(char *name, unsigned char type, const unsigned char *data, char day)
{
    #error "这里仅给出示例，请自行完善天气数据处理代码,完成后请删除该行"
    int value_int;
    char value_string[50];//由于有的参数内容较多，这里默认为50。您可以根据定义的参数，可以适当减少该值
    
    my_memset(value_string, '\0', 50);
    
    //首先获取数据类型
    if(type == 0) { //参数是INT型
        value_int = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];
    }else if(type == 1) {
        my_strcpy(value_string, data);
    }
    
    //注意要根据所选参数类型来获得参数值！！！
    if(my_strcmp(name, "temp") == 0) {
        printf("day:%d temp value is:%d\r\n", day, value_int);          //int 型
    }else if(my_strcmp(name, "humidity") == 0) {
        printf("day:%d humidity value is:%d\r\n", day, value_int);      //int 型
    }else if(my_strcmp(name, "pm25") == 0) {
        printf("day:%d pm25 value is:%d\r\n", day, value_int);          //int 型
    }else if(my_strcmp(name, "condition") == 0) {
        printf("day:%d condition value is:%s\r\n", day, value_string);  //string 型
    }
}

/**
* @brief  mcu主动获取天气服务
 * @param  Null
 * @return Null
 */
void mcu_get_weather(void)
{
    int i = 0;
    char buffer[20] = {0};
    unsigned char weather_len = 0;
    unsigned short send_len = 0;
    
    send_len = set_wifi_uart_byte(send_len, GET_WEATHER_SUBCMD);
    
    weather_len = sizeof(weather_choose) / sizeof(weather_choose[0]);
      
    for(i=0;i<weather_len;i++) {
        buffer[0] = sprintf(buffer+1,"w.%s",weather_choose[i]);
        send_len = set_wifi_uart_buffer(send_len, (unsigned char *)buffer, buffer[0]+1);
    }
    
    #error "请根据提示，自行完善天气服务配置，完成后请删除该行"
    /*
    //当获取的参数有和时间有关的参数时(如:日出日落)，需要搭配t.unix或者t.local使用，需要获取的参数数据是按照格林时间还是本地时间
    buffer[0] = sprintf(buffer+1,"t.unix"); //格林时间   或使用  buffer[0] = sprintf(buffer+1,"t.local"); //本地时间
    send_len = set_wifi_uart_buffer(send_len, (unsigned char *)buffer, buffer[0]+1);
    */
    
    buffer[0] = sprintf(buffer+1,"w.date.%d",WEATHER_FORECAST_DAYS_NUM);
    send_len = set_wifi_uart_buffer(send_len, (unsigned char *)buffer, buffer[0]+1);
    
    wifi_uart_write_frame(EXPAND_FUNC_CMD, MCU_TX_VER, send_len);
}

/**
 * @brief  mcu主动获取天气服务结果
 * @param[in] {result} 获取天气返回结果
 * @ref       0: 成功
 * @ref       1: 失败
 * @param[in] {err} 错误码
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_get_weather_result(unsigned char result)
{
    #error "请自行完成mcu主动获取天气服务结果处理代码,完成后请删除该行"
    
    if(result == 0) {
        //获取成功
    }else {
        //获取失败
    }
}
#endif

#ifdef GREEN_TIME_WITH_ZONE_ENABLE
/**
 * @brief  获取带时区系统（格林）时间数据结果
 * @param[in] {p_data} 数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void get_green_time_with_zone_result(const unsigned char p_data[], unsigned short data_len)
{
    #error "请自行完成获取带时区系统（格林）时间数据结果处理代码,完成后请删除该行"
    
    short time_zone = 0; //时区
    unsigned char summer_time = 0; //夏令时
    
    time_zone = (p_data[0] << 8) | p_data[1];
    summer_time = p_data[2];
    
    if(1 == p_data[3]) {
        //获取时间成功
        /*
        p_data[4]为年份，0x00 表示 2000 年
        p_data[5]为月份，从 1 开始到12 结束
        p_data[6]为日期，从 1 开始到31 结束
        p_data[7]为时钟，从 0 开始到23 结束
        p_data[8]为分钟，从 0 开始到59 结束
        p_data[9]为秒钟，从 0 开始到59 结束
        */
        //time_zone 为时区。例如 -750 表示西7.5区，+800 表示东八区
        //summer_time 表示是否有夏令时  0:表示无  1:表示有
        
        
    }else {
        //获取时间失败
    }
}
#endif


#ifdef SECURITY_PROTECTION_ENABLE
/**
 * @brief  当前布防模式设置结果
 * @param[in] {result} 模块返回结果
 * @return Null
 * @note   MCU需要自行实现该功能
 */
static void defence_mode_set_result(unsigned char result)
{
    #error "请自行实现当前布防模式设置结果处理代码,完成后请删除该行"
    if(0 == result) {
        //成功
    }else {
        //失败
    }
}

/**
 * @brief  当前安防信息获取结果
 * @param[in] {p_data} 数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
static void security_protect_infor_get_result(const unsigned char p_data[], unsigned short data_len)
{
    if(0 != p_data[0]) {
        //失败,后面的数据无效
        return;
    }
    //成功
    
    cJSON *root = NULL,*item = NULL;
    
    char* p_mode = NULL;  //布防模式
    unsigned char alarm = 0;  //报警状态
    unsigned char countdown = 0;  //布防延时状态

    
    char pstr[data_len];
    my_memset(pstr, 0x00, data_len);
    my_memcpy(pstr, &p_data[1], data_len-1);

    root = cJSON_Parse(pstr);
    if(NULL == root){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT;
    }

    item = cJSON_GetObjectItem(root, "mode");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT;
    }
    p_mode = item->valuestring;
    
    item = cJSON_GetObjectItem(root, "alarm");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT;
    }
    alarm = item->valueint;

    item = cJSON_GetObjectItem(root, "countdown");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT;
    }
    countdown = item->valueint;
    
    #error "请自行实现当前安防信息获取结果处理代码,完成后请删除该行"
    //请在此处添加当前安防信息获取结果处理代码,
    // p_mode: 布防模式  “0”:disarm撤防(固定不变)  “1”:在家布防  “2”:离家布防
    // alarm: 报警状态  0：报警延时,报警中  非0：无报警
    // countdown: 布防延时状态  0：布防延时中  非0：无布防延时
    


EXIT:
    cJSON_Delete(root);
}

/**
 * @brief  安防信息同步
 * @param[in] {p_data} 数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
static void security_protect_infor_syn(const unsigned char p_data[], unsigned short data_len)
{
    cJSON *root = NULL,*item = NULL;
    
    char* p_mode = NULL;  //布防模式
    unsigned char delay = 0;  //延时布防时间
    unsigned char sound = 0;  //是否播放声音

    
    char pstr[data_len + 1];
    my_memset(pstr, 0x00, data_len+1);
    my_memcpy(pstr, p_data, data_len);

    root = cJSON_Parse(pstr);
    if(NULL == root){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT;
    }

    item = cJSON_GetObjectItem(root, "mode");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT;
    }
    p_mode = item->valuestring;
    
    item = cJSON_GetObjectItem(root, "delay");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT;
    }
    delay = item->valueint;

    item = cJSON_GetObjectItem(root, "sound");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT;
    }
    sound = item->valueint;
    
    #error "请自行实现当前安防信息同步处理代码,完成后请删除该行"
    //请在此处添加当前安防信息同步处理代码,
    // p_mode: 布防模式  “0”:disarm撤防(固定不变)  “1”:在家布防  “2”:离家布防
    // delay: 延时布防时间  0：表示没有延时；  非0：表示延时时间，单位：s
    // sound: 是否播放声音  0：需要播放；  非0：不需要播放
    


    unsigned short length = 0;
    length = set_wifi_uart_byte(length, SECURITY_PROTECT_INFOR_SYN_SUBCMD); //写入子命令0x02
    wifi_uart_write_frame(SECURITY_PROTECT_INFOR_CMD, MCU_TX_VER, length);
    
EXIT:
    cJSON_Delete(root);
}

/**
 * @brief  设备安防事件同步
 * @param[in] {p_data} 数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
static void dev_security_protect_event_syn(const unsigned char p_data[], unsigned short data_len)
{
    cJSON *root = NULL,*item = NULL;
    
    unsigned char status = 0;  //事件
    char* p_event = NULL;  //事件信息
    
    char pstr[data_len + 1];
    my_memset(pstr, 0x00, data_len+1);
    my_memcpy(pstr, p_data, data_len);

    root = cJSON_Parse(pstr);
    if(NULL == root){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT;
    }

    item = cJSON_GetObjectItem(root, "status");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT;
    }
    status = item->valueint;
    
    item = cJSON_GetObjectItem(root, "data");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT;
    }
    p_event = item->valuestring;
    
    #error "请自行实现当前安防信息同步处理代码,完成后请删除该行"
    //请在此处添加当前安防信息同步处理代码,
    // status: 事件  0:disarm撤防；  1:进入布防（倒计时后在家或离家）；  2:有忽略事件发生，主要用于触发播放声音；  3：倒计时开始
    // p_event: 事件信息  “0”：表示无倒计时,目前只在事件报警倒计时时反馈倒计时时间
    


    unsigned short length = 0;
    length = set_wifi_uart_byte(length, DEV_SECURITY_PROTECT_EVENT_SYN_SUBCMD); //写入子命令0x03
    wifi_uart_write_frame(SECURITY_PROTECT_INFOR_CMD, MCU_TX_VER, length);
    
EXIT:
    cJSON_Delete(root);
}

/**
 * @brief  安防信息相关结果
 * @param[in] {p_data} 数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void security_protect_infor_result(const unsigned char p_data[], unsigned short data_len)
{
    switch(p_data[0]) { //子命令
        case DEFENCE_MODE_SET_SUBCMD:
            if(2 != data_len) {
                //可在此添加提示信息，如：printf("xxx");
                return;
            }
            defence_mode_set_result(p_data[1]);
        break;
        case SECURITY_PROTECT_INFOR_GET_SUBCMD:
            if(2 > data_len) {
                //可在此添加提示信息，如：printf("xxx");
                return;
            }
            security_protect_infor_get_result(&p_data[1], data_len - 1);
        break;
        case SECURITY_PROTECT_INFOR_SYN_SUBCMD:
            if(2 > data_len) {
                //可在此添加提示信息，如：printf("xxx");
                return;
            }
            security_protect_infor_syn(&p_data[1], data_len - 1);
        break;
        case DEV_SECURITY_PROTECT_EVENT_SYN_SUBCMD:
            if(2 > data_len) {
                //可在此添加提示信息，如：printf("xxx");
                return;
            }
            dev_security_protect_event_syn(&p_data[1], data_len - 1);
        break;
        default:break;
    }
}

/**
 * @brief  报警状态设置结果
 * @param[in] {result} 模块返回结果
 * @return Null
 * @note   MCU需要自行实现该功能
 */
static void alarm_state_set_result(unsigned char result)
{
    #error "请自行实现报警状态设置结果处理代码,完成后请删除该行"
    if(0 == result) {
        //成功
    }else {
        //失败
    }
}

#ifndef SECURITY_PROTECTION_ALARM_DISPLAY_ENABLE
/**
 * @brief  取消报警状态同步
 * @param[in] {result} 模块返回结果
 * @return Null
 * @note   MCU需要自行实现该功能
 */
static void cancel_alarm_state_syn(unsigned char result)
{
    #error "请自行实现取消报警状态同步处理代码,完成后请删除该行"
    if(0 == result) {
        //成功取消报警
    }else {
        //失败
    }
    
    unsigned short length = 0;
    length = set_wifi_uart_byte(length, CANCEL_ALARM_STATE_SET_SUBCMD); //写入子命令
    wifi_uart_write_frame(SECURITY_PROTECT_ALARM_CMD, MCU_TX_VER, length);
}

/**
 * @brief  设备报警信息同步
 * @param[in] {p_data} 数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
static void dev_alarm_infor_syn(const unsigned char p_data[], unsigned short data_len)
{
    cJSON *root = NULL,*item = NULL;
    
    unsigned char type = 0;  //触发报警设备类型
    char* p_subid = NULL;  //子设备id
    char* p_dp_inf = NULL;  //触发报警dp信息
    
    char pstr[data_len + 1];
    my_memset(pstr, 0x00, data_len+1);
    my_memcpy(pstr, p_data, data_len);

    root = cJSON_Parse(pstr);
    if(NULL == root){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT;
    }

    item = cJSON_GetObjectItem(root, "type");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT;
    }
    type = item->valueint;
    
    item = cJSON_GetObjectItem(root, "sub_id");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT;
    }
    p_subid = item->valuestring;
    
    item = cJSON_GetObjectItem(root, "dp_inf");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT;
    }
    p_dp_inf = item->valuestring;
    
    #error "请自行实现设备报警信息同步处理代码,完成后请删除该行"
    //请在此处添加设备报警信息同步处理代码,
    // type: 触发报警设备类型  0：非环境设备；  1：环境设备.
    // p_subid: 子设备id
    // p_dp_inf: 触发报警dp信息，cjson字符串



    unsigned short length = 0;
    length = set_wifi_uart_byte(length, DEV_ALARM_INFOR_SYN_SUBCMD); //写入子命令0x02
    wifi_uart_write_frame(SECURITY_PROTECT_ALARM_CMD, MCU_TX_VER, length);
    
EXIT:
    cJSON_Delete(root);
}
#endif

/**
 * @brief  设备报警延时状态同步
 * @param[in] {result} 模块返回结果
 * @return Null
 * @note   MCU需要自行实现该功能
 */
static void dev_alarm_delay_state_syn(unsigned char result)
{
    #error "请自行实现设备报警延时状态同步代码,完成后请删除该行"
    switch(result) {
        case 0:
            //报警延时未创建
        break;
        case 1:
            //报警延时进行中
        break;
        case 2:
            //报警延时结束
        break;
        default:break;
    }
    
    unsigned short length = 0;
    length = set_wifi_uart_byte(length, DEV_ALARM_DELAY_STATE_SUBCMD); //写入子命令
    wifi_uart_write_frame(SECURITY_PROTECT_ALARM_CMD, MCU_TX_VER, length);
}

#ifdef SECURITY_PROTECTION_ALARM_DISPLAY_ENABLE
/**
 * @brief  新设备报警信息显示同步
 * @param[in] {p_data} 数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
static void new_dev_alarm_infor_syn(const unsigned char p_data[], unsigned short data_len)
{
    cJSON *root = NULL,*item = NULL;
    
    unsigned char type = 0;  //触发报警设备类型
    char* p_subid = NULL;  //子设备id
    char* p_dp_inf = NULL;  //触发报警dp信息
    char* p_gp = NULL;  //防区
    
    char pstr[data_len + 1];
    my_memset(pstr, 0x00, data_len+1);
    my_memcpy(pstr, p_data, data_len);

    root = cJSON_Parse(pstr);
    if(NULL == root){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT;
    }

    item = cJSON_GetObjectItem(root, "type");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT;
    }
    type = item->valueint;
    
    item = cJSON_GetObjectItem(root, "sub_id");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT;
    }
    p_subid = item->valuestring;
    
    item = cJSON_GetObjectItem(root, "dp_inf");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT;
    }
    p_dp_inf = item->valuestring;
    
    item = cJSON_GetObjectItem(root, "gp");
    if(NULL == item){
        //可在此添加提示信息，如：printf("xxx");
        goto EXIT;
    }
    p_gp = item->valuestring;
    
    #error "请自行实现新设备报警信息显示同步处理代码,完成后请删除该行"
    //请在此处添加设备报警信息同步处理代码,
    // type: 触发报警设备类型  0：非环境设备；  1：环境设备.
    // p_subid: 子设备id
    // p_dp_inf: 触发报警dp信息，cjson字符串
    // p_gp: 防区。为多防区功能使用，同步报警设备属于哪个防区中的
    
    
    
    unsigned short length = 0;
    length = set_wifi_uart_byte(length, NEW_DEV_ALARM_INFOR_DISPLAY_SYN_SUBCMD); //写入子命令0x02
    wifi_uart_write_frame(SECURITY_PROTECT_ALARM_CMD, MCU_TX_VER, length);
    
EXIT:
    cJSON_Delete(root);
}

/**
 * @brief  新设备报警状态同步
 * @param[in] {result} 模块返回结果
 * @return Null
 * @note   MCU需要自行实现该功能
 */
static void new_dev_alarm_state_syn(unsigned char result)
{
    #error "请自行实现新设备报警状态同步处理代码,完成后请删除该行"
    if(0 == result) {
        //取消报警
    }else {
        //报警中
    }
    
    unsigned short length = 0;
    length = set_wifi_uart_byte(length, NEW_DEV_ALARM_DELAY_STATE_SUBCMD); //写入子命令
    wifi_uart_write_frame(SECURITY_PROTECT_ALARM_CMD, MCU_TX_VER, length);
}
#endif

/**
 * @brief  报警相关结果
 * @param[in] {p_data} 数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void alarm_infor_result(const unsigned char p_data[], unsigned short data_len)
{
    switch(p_data[0]) { //子命令
        case ALARM_STATE_SET_SUBCMD:
            if(2 != data_len) {
              //可在此添加提示信息，如：printf("xxx");
              return;
            }
            alarm_state_set_result(p_data[1]);
        break;
#ifndef SECURITY_PROTECTION_ALARM_DISPLAY_ENABLE
        case CANCEL_ALARM_STATE_SET_SUBCMD:
            if(2 != data_len) {
              //可在此添加提示信息，如：printf("xxx");
              return;
            }
            cancel_alarm_state_syn(p_data[1]);
        break;
        case DEV_ALARM_INFOR_SYN_SUBCMD:
            if(2 > data_len) {
              //可在此添加提示信息，如：printf("xxx");
              return;
            }
            dev_alarm_infor_syn(&p_data[1], data_len - 1);
        break;
#endif
        case DEV_ALARM_DELAY_STATE_SUBCMD:
            if(2 != data_len) {
              //可在此添加提示信息，如：printf("xxx");
              return;
            }
            dev_alarm_delay_state_syn(p_data[1]);
        break;
#ifdef SECURITY_PROTECTION_ALARM_DISPLAY_ENABLE
        case NEW_DEV_ALARM_INFOR_DISPLAY_SYN_SUBCMD:
            if(2 > data_len) {
              //可在此添加提示信息，如：printf("xxx");
              return;
            }
            new_dev_alarm_infor_syn(&p_data[1], data_len - 1);
        break;
        case NEW_DEV_ALARM_DELAY_STATE_SUBCMD:
            if(2 != data_len) {
              //可在此添加提示信息，如：printf("xxx");
              return;
            }
            new_dev_alarm_state_syn(p_data[1]);
        break;
#endif
        default:break;
    }
}
#endif

