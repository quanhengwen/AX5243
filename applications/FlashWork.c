#include "rtthread.h"
#include "rtdevice.h"
#include "pin_config.h"
#include "FlashWork.h"
#include <easyflash.h>
#include <fal.h>
#include <stdlib.h>

#define DBG_TAG "flash"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

typedef struct _env_list {
    char *key;
} env_list;
uint32_t Flash_Get_Boot_Times(void)
{
    char *tempbuf = rt_malloc(10);//申请临时buffer空间
    const char *keybuf="boot_times";
    uint32_t read_value = 0;//真实值
    size_t len;//长度
    ef_get_env_blob(keybuf, NULL, 0, &len);//获取长度
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
    size_t len;//长度
    ef_get_env_blob(keybuf, NULL, 0, &len);//获取长度
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
    size_t len;//长度
    sprintf(tempkey, "%ld", key);//将传入的数字转换成数组
    ef_get_env_blob(tempkey, NULL, 0, &len);//获取长度
    ef_get_env_blob(tempkey, tempbuf, len , NULL);//通过长度获取数据
    read_value = atol(tempbuf);//转换数组为真实数据
    rt_free(tempbuf);//释放临时buffer对应内存空间
    rt_free(tempkey);//释放临时buffer对应内存空间
    LOG_D("Reading value %ld ,len is %ld\r\n",read_value,len);//输出
    return read_value;
}
uint8_t Flash_Get_Key_Valid(uint32_t key)
{
    char *tempkey = rt_malloc(10);//申请临时buffer空间
    size_t len=0;//长度
    sprintf(tempkey, "%ld", key);//将传入的数字转换成数组
    ef_get_env_blob(tempkey, NULL, 0, &len);//获取长度
    rt_free(tempkey);//释放临时buffer对应内存空间
    LOG_D("Reading key %ld is %ld\r\n",key,len);//输出
    if(len>0)return 1;
    else return 0;
}
//void flash_test(uint32_t key)
//{
//    char *tempbuf = rt_malloc(10);//申请临时buffer空间
//    char *tempkey = rt_malloc(10);//申请临时buffer空间
//    uint32_t read_value = 0;//真实值
//    size_t len;//长度
//    sprintf(tempkey, "%ld", key);//将传入的数字转换成数组
//    ef_get_env_blob(tempkey, NULL, 0, &len);//获取长度
//    ef_get_env_blob(tempkey, tempbuf, len , NULL);//通过长度获取数据
//    read_value = atol(tempbuf);//转换数组为真实数据
//    rt_free(tempbuf);//释放临时buffer对应内存空间
//    rt_free(tempkey);//释放临时buffer对应内存空间
//    LOG_D("Reading value %ld ,len is %ld\r\n", read_value,len);//输出
//}
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
void Flash_Key_Delete(uint32_t key)
{
    char Temp_KeyBuf[10] = {0};
    sprintf(Temp_KeyBuf, "%ld", key);
    ef_set_env(Temp_KeyBuf, RT_NULL);
    ef_save_env();
    LOG_D("Key %ld is Deleted",key);
}

void D_test(void)
{
    Flash_Key_Delete(20022636);
}
MSH_CMD_EXPORT(D_test,D_test);
void Z_test(void)
{
    Flash_Key_Delete(12345678);
}
MSH_CMD_EXPORT(Z_test,Z_test);
void F_test(void)
{
    for(uint16_t i=0;i<5000;i++)
    {
        Flash_Key_Change(20000000+i,10000000+i);
    }
}
MSH_CMD_EXPORT(F_test,F_test);
void C_test(void)
{
    Flash_Key_Change(88888989,0);
    Flash_Get_Key_Valid(11111111);
    Flash_Get_Key_Valid(88888989);
}
MSH_CMD_EXPORT(C_test,C_test);


