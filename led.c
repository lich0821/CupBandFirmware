
#include "nrf_gpio.h"
#include "led.h"

void led_init(void)
{
	// Configure LED-pins as outputs
	nrf_gpio_cfg_output(LED_0);
	nrf_gpio_cfg_output(LED_1);
	
	nrf_gpio_pin_set(LED_0);
	nrf_gpio_pin_set(LED_1);
}

void LED1_Open(void)
{
	nrf_gpio_pin_clear(LED_0);
}

void LED1_Close(void)
{
	nrf_gpio_pin_set(LED_0);
}
void LED1_Toggle(void)
{
	nrf_gpio_pin_toggle(LED_0);
}
void moto_Toggle(void)
{
	nrf_gpio_pin_toggle(moto);
}
void LED2_Open(void)
{
	nrf_gpio_pin_clear(LED_1);
}

void LED2_Close(void)
{
	nrf_gpio_pin_set(LED_1);
}
void LED2_Toggle(void)
{
	nrf_gpio_pin_toggle(LED_1);
}
 
