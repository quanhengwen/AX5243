#include <agile_led.h>
#include <stdlib.h>
#include "led.h"
#include "pin_config.h"

static agile_led_t *led0 = RT_NULL;
static agile_led_t *led1 = RT_NULL;

#define DBG_TAG "led"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

void led_Init(void)
{
    if(led0 == RT_NULL)
    {
        led0 = agile_led_create(LED0_PIN, PIN_LOW, "100,200", -1);
        LOG_D("LED_0 Init Success\r\n");
    }

    if(led1 == RT_NULL)
    {
        led1 = agile_led_create(LED1_PIN, PIN_LOW, "200,100", -1);
        LOG_D("LED_1 Init Success\r\n");
    }

}

void led_Slow_Start(uint8_t led_id,uint8_t count)
{
    switch (led_id)
    {
    case 0:
        agile_led_set_light_mode(led0, "500,1000", count);
        agile_led_start(led0);
        break;

    case 1:
        agile_led_set_light_mode(led1, "500,1000", count);
        agile_led_start(led1);
        break;
    }

}
void led_Fast_Start(uint8_t led_id,uint8_t count)
{
    switch (led_id)
    {
    case 0:
        agile_led_set_light_mode(led0, "200,300", count);
        agile_led_start(led0);
        break;

    case 1:
        agile_led_set_light_mode(led1, "200,300", count);
        agile_led_start(led1);
        break;
    }

}
void led_Stop(uint8_t led_id)
{
    switch (led_id)
    {
    case 0:
        agile_led_stop(led0);
        break;

    case 1:
        agile_led_stop(led1);
        break;
    }
}
