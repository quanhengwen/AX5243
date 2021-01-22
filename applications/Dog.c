#include <rtthread.h>
#include <rtdevice.h>
#include "dog.h"

#define WDT_DEVICE_NAME    "wdt"    /* 看门狗设备名称 */

#define DBG_TAG "WatchDog"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

static rt_device_t wdg_dev;         /* 看门狗设备句柄 */

void FeedDog(void)
{
    rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, NULL);
}
int wdt_sample(void)
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t timeout = 5;        /* 溢出时间，单位：秒 */
    char device_name[RT_NAME_MAX];

    /* 判断命令行参数是否给定了设备名称 */
    rt_strncpy(device_name, WDT_DEVICE_NAME, RT_NAME_MAX);
    /* 根据设备名称查找看门狗设备，获取设备句柄 */
    wdg_dev = rt_device_find(device_name);
    if (!wdg_dev)
    {
        LOG_D("find %s failed!\n", device_name);
        return RT_ERROR;
    }
    /* 初始化设备 */
    ret = rt_device_init(wdg_dev);
    if (ret != RT_EOK)
    {
        LOG_D("initialize %s failed!\n", device_name);
        return RT_ERROR;
    }
    /* 设置看门狗溢出时间 */
    ret = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &timeout);
    if (ret != RT_EOK)
    {
        LOG_D("set %s timeout failed!\n", device_name);
        return RT_ERROR;
    }
    /* 启动看门狗 */
    ret = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_START, RT_NULL);
    if (ret != RT_EOK)
    {
        LOG_D("start %s failed!\n", device_name);
        return -RT_ERROR;
    }
    LOG_D("WatchDog Init Success\r\n");
    return ret;
}
