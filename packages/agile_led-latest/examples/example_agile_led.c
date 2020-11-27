#include <agile_led.h>
#include <stdlib.h>
#include "led.h"
#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

#define LED0_PIN    32
#define LED1_PIN    34

static agile_led_t *led0 = RT_NULL;
static agile_led_t *led1 = RT_NULL;

void led_Init(void)
{
    if(led0 == RT_NULL)
    {
        led0 = agile_led_create(LED0_PIN, PIN_LOW, "100,200", -1);
    }

    if(led1 == RT_NULL)
    {
        led1 = agile_led_create(LED1_PIN, PIN_LOW, "200,100", -1);
    }

}

void led_Start(uint8_t led_id,const char *light_mode)
{
    switch (led_id)
    {
    case 0:
        led = led0;
        break;

    case 1:
        led = led1;
        break;
    }
    if(led == RT_NULL)return;
    agile_led_start(led);
    agile_led_set_light_mode(led, light_mode, loop_cnt);
}

void led_Stop(uint8_t led_id)
{
    switch (led_id)
    {
    case 0:
        led = led0;
        break;

    case 1:
        led = led1;
        break;
    }
    if(led == RT_NULL)return;
    agile_led_stop(led);
}
