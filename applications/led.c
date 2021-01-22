#include <agile_led.h>
#include <stdlib.h>
#include "led.h"
#include "pin_config.h"

static agile_led_t *led0 = RT_NULL;
static agile_led_t *led1 = RT_NULL;
static agile_led_t *beep = RT_NULL;
static agile_led_t *singlebeep = RT_NULL;
static agile_led_t *singleled0 = RT_NULL;
static agile_led_t *lossled0 = RT_NULL;

#define DBG_TAG "led"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

uint8_t led_id_temp = 0;
uint8_t led_mode_temp = 0;

void led_Init(void)
{
    if(led0 == RT_NULL)
    {
        led0 = agile_led_create(LED0_PIN, PIN_LOW, "200,200", -1);
        singleled0 = agile_led_create(LED0_PIN, PIN_LOW, "200,1", 1);
        lossled0 = agile_led_create(LED0_PIN, PIN_LOW, "200,200,200,5000", -1);
        LOG_D("LED_0 Init Success\r\n");
    }

    if(led1 == RT_NULL)
    {
        led1 = agile_led_create(LED1_PIN, PIN_LOW, "200,200", -1);
        LOG_D("LED_1 Init Success\r\n");
    }

    if(beep == RT_NULL)
    {
        beep = agile_led_create(0, PIN_HIGH, "200,200", -1);
        singlebeep = agile_led_create(0, PIN_HIGH, "200,1", 1);
        LOG_D("Beep Init Success\r\n");
    }

}
void beeplive(void)
{
    agile_led_lock(led0);
    agile_led_lock(singleled0);
    agile_led_lock(lossled0);
    LOG_D("Led 0 is Lock\r\n");
    rt_pin_write(LED0_PIN,0);
}
void beepback(void)
{
    agile_led_unlock(led0);
    agile_led_unlock(singleled0);
    agile_led_unlock(lossled0);
    rt_pin_write(LED0_PIN,1);
    LOG_D("Led 0 is UnLock\r\n");
}
void loss_led_start(void)
{
    agile_led_start(lossled0);
}
void loss_led_stop(void)
{
    agile_led_stop(lossled0);
}
void beep_start(uint8_t led_id,int mode)
{
    agile_led_stop(singlebeep);
    agile_led_stop(singleled0);
    led_id_temp = led_id;
    led_mode_temp = mode;
    switch (mode)
    {
    case 0:
        if(led_id)//绿灯
        {
            agile_led_set_light_mode(beep, "200,200", 1);
            agile_led_start(beep);
            agile_led_set_light_mode(led1, "200,200", 1);
            agile_led_start(led1);
        }
        else//红灯
        {
            agile_led_set_light_mode(beep, "200,15000", -1);
            agile_led_start(beep);
            agile_led_set_light_mode(led0, "200,15000", -1);
            agile_led_start(led0);
        }
        break;

    case 1:
        agile_led_set_light_mode(beep, "200,200,200,5000", -1);
        agile_led_start(beep);
        if(led_id)
        {
            agile_led_set_light_mode(led1, "200,200,200,5000", -1);
            agile_led_start(led1);
        }
        else
        {
            agile_led_set_light_mode(led0, "200,200,200,5000", -1);
            agile_led_start(led0);
        }
        break;

    case 2:
        agile_led_set_light_mode(beep, "200,200,200,200,200,5000", -1);
        agile_led_start(beep);
        if(led_id)
        {
            agile_led_set_light_mode(led1, "200,200,200,200,200,5000", -1);
            agile_led_start(led1);
        }
        else
        {
            agile_led_set_light_mode(led0, "200,200,200,200,200,5000", -1);
            agile_led_start(led0);
        }
        break;
    case 3:
        agile_led_set_light_mode(beep, "200,200,200,200,200,200,200,5000", -1);
        agile_led_start(beep);
        if(led_id)
        {
            agile_led_set_light_mode(led1, "200,200,200,200,200,200,200,5000", -1);
            agile_led_start(led1);
        }
        else
        {
            agile_led_set_light_mode(led0, "200,200,200,200,200,200,200,5000", -1);
            agile_led_start(led0);
        }
        break;
    case 4://五声
        agile_led_set_light_mode(beep, "200,200,200,200,200,200,200,200,200,5000", -1);
        agile_led_start(beep);
        if(led_id)
        {
            agile_led_set_light_mode(led1, "200,200,200,200,200,200,200,200,200,5000", -1);
            agile_led_start(led1);
        }
        else
        {
            agile_led_set_light_mode(led0, "200,200,200,200,200,200,200,200,200,5000", -1);
            agile_led_start(led0);
        }
        break;
    case 5://四声
        agile_led_set_light_mode(beep, "200,200,200,200,200,200,200,5000", -1);
        agile_led_start(beep);
        if(led_id)
        {
            agile_led_set_light_mode(led1, "200,200,200,200,200,200,200,5000", -1);
            agile_led_start(led1);
        }
        else
        {
            agile_led_set_light_mode(led0, "200,200,200,200,200,200,200,5000", -1);
            agile_led_start(led0);
        }
        break;
    case 6:
        agile_led_set_light_mode(beep, "200,200", 1);
        agile_led_start(beep);
        if(led_id)
        {
            agile_led_set_light_mode(led1, "200,200", 1);
            agile_led_start(led1);
        }
        else
        {
            agile_led_stop(led0);
            agile_led_set_light_mode(led0, "200,200", 1);
            agile_led_start(led0);
        }
        break;
    case 7:
        agile_led_set_light_mode(beep, "200,200", 3);
        agile_led_start(beep);
        if(led_id)
        {
            agile_led_set_light_mode(led1, "200,200", 3);
            agile_led_start(led1);
        }
        else
        {
            agile_led_stop(led0);
            agile_led_set_light_mode(led0, "200,200", 3);
            agile_led_start(led0);
        }
        break;
    case 8:
        agile_led_set_light_mode(beep, "200,200", 5);
        agile_led_start(beep);
        if(led_id)
        {
            agile_led_set_light_mode(led1, "200,200", 5);
            agile_led_start(led1);
        }
        else
        {
            agile_led_stop(led0);
            agile_led_set_light_mode(led0, "200,200", 5);
            agile_led_start(led0);
        }
        break;

    case 9://五声
        agile_led_set_light_mode(beep, "200,200,200,200,200,200,200,200,200,200,200,5000", -1);
        agile_led_start(beep);
        if(led_id)
        {
            agile_led_set_light_mode(led1, "200,200,200,200,200,200,200,200,200,200,200,5000", -1);
            agile_led_start(led1);
        }
        else
        {
            agile_led_set_light_mode(led0, "200,200,200,200,200,200,200,200,200,200,200,5000", -1);
            agile_led_start(led0);
        }
        break;
    }
}
void beep_stop(void)
{
    agile_led_stop(beep);
    rt_pin_write(0, 0);
}
void key_down(void)
{
    agile_led_start(singlebeep);
    agile_led_start(singleled0);
}
void just_ring(void)
{
    agile_led_start(singlebeep);
}
void led_Long_Start(uint8_t led_id)
{
    switch (led_id)
    {
    case 0:
        agile_led_set_light_mode(led0, "200,200", -1);
        agile_led_start(led0);
        led_Stop(1);
        break;

    case 1:
        agile_led_set_light_mode(led1, "200,0", -1);
        agile_led_start(led1);
        led_Stop(0);
        break;
    }
}
void led_Slow_Start(uint8_t led_id,int count)
{
    switch (led_id)
    {
    case 0:
        agile_led_set_light_mode(led0, "200,2000", count);
        agile_led_start(led0);
        led_Stop(1);
        break;

    case 1:
        agile_led_set_light_mode(led1, "200,2000", count);
        agile_led_start(led1);
        led_Stop(0);
        break;
    }
}
void led_Fast_Start(uint8_t led_id,int count)
{
    switch (led_id)
    {
    case 0:
        agile_led_set_light_mode(led0, "200,300", count);
        agile_led_start(led0);
        led_Stop(1);
        break;

    case 1:
        agile_led_set_light_mode(led1, "200,300", count);
        agile_led_start(led1);
        led_Stop(0);
        break;
    }

}
void led_Stop(uint8_t led_id)
{
    switch (led_id)
    {
    case 0:
        agile_led_stop(led0);
        rt_pin_write(LED0_PIN, 1);
        break;
    case 1:
        agile_led_stop(led1);
        rt_pin_write(LED1_PIN, 1);
        break;
    case 2:
        agile_led_stop(beep);
        rt_pin_write(0, 0);
        break;
    case 3:
        agile_led_stop(singleled0);
        rt_pin_write(0, 0);
        break;
    case 4:
        agile_led_stop(led0);
        agile_led_stop(led1);
        agile_led_stop(beep);
        agile_led_stop(singlebeep);
        agile_led_stop(singleled0);
        break;
    }
}
void led_on(uint8_t id)
{
    switch(id)
    {
    case 0:agile_led_on(led0);agile_led_off(led1);break;
    case 1:agile_led_on(led1);agile_led_off(led0);break;
    }

}
