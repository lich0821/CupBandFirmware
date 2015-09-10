#ifndef __LED_H
#define	__LED_H

#include "nrf51.h"

 
#define LED_0          14   //ºìÉ« led1
#define LED_1          16    //15  //À¶É«  led2
#define moto            9
 
void led_init(void);
void LED1_Open(void);
void LED1_Close(void);
void LED1_Toggle(void);
void LED2_Open(void);
void LED2_Close(void);
void LED2_Toggle(void);
void LED3_Toggle(void);
void moto_Toggle(void);

#endif /* __LED_H */
