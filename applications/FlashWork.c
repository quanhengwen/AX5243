#include "rtthread.h"
#include "rtdevice.h"
#include "pin_config.h"
#include "FlashWork.h"
#include <easyflash.h>
#include <fal.h>
#include <stdlib.h>
#include <string.h>

#define DBG_TAG "flash"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

typedef struct _env_list {
    char *key;
} env_list;
typedef struct
{
    uint32_t Num;
    uint32_t ID[50];
    uint32_t ID_Time[50];
}Device_Info;

Device_Info Global_Device={0};
void Boot_Times_Record(void)
{
    uint32_t i_boot_times = 0;
    char *c_old_boot_times, c_new_boot_times[11] = {0};

    /* 从环境变量中获取启动次数 */
    c_old_boot_times = ef_get_env("boot_times");
    /* 获取启动次数是否失败 */
    if (c_old_boot_times == RT_NULL)
        c_old_boot_times[0] = '0';

    i_boot_times = atol(c_old_boot_times);
    /* 启动次数加 1 */
    i_boot_times++;
    LOG_D("===============================================");
    LOG_D("The system now boot %d times", i_boot_times);
    LOG_D("===============================================");
    /* 数字转字符串 */
    sprintf(c_new_boot_times, "%ld", i_boot_times);
    /* 保存开机次数的值 */
    ef_set_env("boot_times", c_new_boot_times);
    ef_save_env();
}
uint32_t Flash_Get_Boot_Times(void)
{
    char *tempbuf = rt_malloc(10);//申请临时buffer空间
    const char *keybuf="boot_times";
    uint32_t read_value = 0;//真实值
    size_t len=0;//长度
    ef_get_env_blob(keybuf, NULL, 0, &len);//获取长度
    if(!len)return 0;//如果空直接传出
    ef_get_env_blob(keybuf, tempbuf, len , NULL);//通过长度获取数据
    read_value = atol(tempbuf);//转换数组为真实数据
    rt_free(tempbuf);//释放临时buffer对应内存空间
    LOG_D("Reading value %ld ,len is %ld\r\n", read_value,len);//输出
    return read_value;
}
MSH_CMD_EXPORT(Flash_Get_Boot_Times,Flash_Get_Boot_Times);
uint32_t Flash_Get_Learn_Nums(void)
{
    char *tempbuf = rt_malloc(10);//申请临时buffer空间
    const char *keybuf="Learn_Nums";
    uint32_t read_value = 0;//真实值
    size_t len=0;//长度
    ef_get_env_blob(keybuf, NULL, 0, &len);//获取长度
    if(!len)return 0;//如果空直接传出
    ef_get_env_blob(keybuf, tempbuf, len , NULL);//通过长度获取数据
    read_value = atol(tempbuf);//转换数组为真实数据
    rt_free(tempbuf);//释放临时buffer对应内存空间
    LOG_D("Reading value %ld ,len is %ld\r\n", read_value,len);//输出
    return read_value;
}
MSH_CMD_EXPORT(Flash_Get_Learn_Nums,Flash_Get_Learn_Nums);
uint32_t Flash_Get_Key_Value(uint32_t key)
{
    char *tempbuf = rt_malloc(10);//申请临时buffer空间
    char *tempkey = rt_malloc(10);//申请临时buffer空间
    uint32_t read_value = 0;//真实值
    size_t len=0;//长度
    sprintf(tempkey, "%ld", key);//将传入的数字转换成数组
    ef_get_env_blob(tempkey, NULL, 0, &len);//获取长度
    if(!len)return 0;//如果空直接传出
    ef_get_env_blob(tempkey, tempbuf, len , NULL);//通过长度获取数据
    read_value = atol(tempbuf);//转换数组为真实数据
    rt_free(tempbuf);//释放临时buffer对应内存空间
    rt_free(tempkey);//释放临时buffer对应内存空间
    LOG_D("Reading value %ld ,len is %ld\r\n",read_value,len);//输出
    return read_value;
}
void Flash_Key_Change(uint32_t key,uint32_t value)
{
    char Temp_KeyBuf[10] = {0};
    sprintf(Temp_KeyBuf, "%ld", key);
    char Temp_ValueBuf[10] = {0};
    sprintf(Temp_ValueBuf, "%ld", value);
    ef_set_env(Temp_KeyBuf, Temp_ValueBuf);
    ef_save_env();
    LOG_D("Writing %ld to key %ld \r\n", value,key);
}
void Flash_LearnNums_Change(uint32_t value)
{
    const char *keybuf="Learn_Nums";
    char Temp_ValueBuf[10] = {0};
    sprintf(Temp_ValueBuf, "%ld", value);
    ef_set_env(keybuf, Temp_ValueBuf);
    ef_save_env();
    LOG_D("Writing %ld to key %s\r\n", value,keybuf);
}
uint8_t Add_Device(uint32_t Device_ID)
{
    uint32_t Num=0;
    Num = Flash_Get_Learn_Nums();
    if(Num>30)return RT_ERROR;
    Flash_LearnNums_Change(++Num);
    Global_Device.Num = Num;
    Global_Device.ID[Num] = Device_ID;
    Flash_Key_Change(Num,Device_ID);
    return RT_EOK;
}
uint8_t Delete_Device(uint32_t Device_ID)
{
    uint32_t Num=0;
    Num = Flash_Get_Learn_Nums();
    if(Num<1)return RT_ERROR;
    Global_Device.ID[Num] = 0;
    Flash_LearnNums_Change(--Num);
    Global_Device.Num = Num;
    Flash_Key_Change(Num,Device_ID);
    return RT_EOK;
}
uint8_t Update_Device_Time(uint32_t Device_ID,uint32_t TimeCount)//更新时间戳
{
    uint16_t num = Global_Device.Num;
    do
    {
        if(Global_Device.ID[num]==Device_ID)
        {
            Global_Device.ID_Time[num] += 1;
            LOG_D("Device %d is Increase to %d",Global_Device.ID[num],TimeCount);
            return RT_EOK;
        }
    }
    while(num--);
    LOG_D("Device %d is Not Increase Success",Global_Device.ID[num]);
    return RT_ERROR;
}
uint8_t Clear_Device_Time(uint32_t Device_ID)//更新时间戳为0
{
    uint16_t num = Global_Device.Num;
    do
    {
        if(Global_Device.ID[num]==Device_ID)
        {
            Global_Device.ID_Time[num] = 0;
            LOG_D("Device %d is Clear to 0",Global_Device.ID[num]);
            return RT_EOK;
        }
    }
    while(num--);
    LOG_D("Device %d is Not Clear Success",Global_Device.ID[num]);
    return RT_ERROR;
}
void Update_All_Time(void)
{
    uint16_t Num = Global_Device.Num;
    uint32_t Time = 0;
    for(uint8_t i=0;i<=Num;i++)
    {
        Time = Global_Device.ID_Time[i];//查询剩余时间
        Time++;                         //自增
        Global_Device.ID_Time[i] = Time;//更新内存中的时间
    }
}
void Clear_All_Time(void)
{
    uint16_t Num = Global_Device.Num;
    for(uint8_t i=0;i<=Num;i++)
    {
        Global_Device.ID_Time[i] = 0;//更新内存中的时间
    }
}
void Detect_All_Time(void)
{
    uint16_t num = Global_Device.Num;
    do
    {
        if(Global_Device.ID_Time[num]>=24)
        {
            //掉线ID上报
        }
    }
    while(num--);
    Clear_All_Time();
}
uint8_t Flash_Get_Key_Valid(uint32_t Device_ID)//查询内存中的ID
{
    uint16_t num = Global_Device.Num;
    do
    {
        if(Global_Device.ID[num]==Device_ID)return RT_EOK;
    }
    while(num--);
    return RT_ERROR;
}
void LoadDevice2Memory(void)//数据载入到内存中
{
    memset(&Global_Device,0,sizeof(Global_Device));
    Global_Device.Num = Flash_Get_Learn_Nums();
    LOG_D("num is %d",Global_Device.Num);
    for(uint8_t i=0;i<=Global_Device.Num;i++)
    {
        Global_Device.ID[i] = Flash_Get_Key_Value(i);
        LOG_D("GOT ID is %ld",Global_Device.ID[i]);
    }
}
MSH_CMD_EXPORT(LoadDevice2Memory,LoadDevice2Memory);
void test11(void)
{
    Add_Device(11111110);
    Add_Device(11111111);
    Add_Device(11111112);
    Add_Device(11111113);
}
MSH_CMD_EXPORT(test11,test11);
