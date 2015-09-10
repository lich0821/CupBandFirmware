

#ifndef __OLED_H
#define __OLED_H			  	 
#include "spi.h"

#define oled_site 0    //1=0.96;0=0.66

void oled_clear(void);     //清屏函数
void oled_display_on(void);          //开启oled
void oled_display_off(void);     //关闭oled
void oled_set_pos(unsigned char x, unsigned char y); //移动点
void oled_init(void);
void oled_display_16(unsigned char x,unsigned char y,unsigned char *data_s);   //16*16
void oled_display_8(unsigned char x,unsigned char y,unsigned char *data_s);    //8*16

void oled_display_1532(unsigned char x,unsigned char y,unsigned char data);
void oled_display_T(void);
void oled_display_816(unsigned char x,unsigned char y,unsigned char data);
void oled_display_1532num2(unsigned char x,unsigned char y,unsigned char num);   //显示2个数据1532
void oled_display_816int16(uint8_t x,uint8_t y,short int num);
void oled_display_816num4(uint8_t x,uint8_t y,uint16_t num);                    //显示不确定数据长度
void oled_display_816ico(unsigned char x,unsigned char y,unsigned char data);//显示图标
void oled_display_816num2(unsigned char x,unsigned char y,unsigned char num);//显示2个数据816
void oled_showstr(uint8_t x,uint8_t y,unsigned char *p);

void oled_display_Taiji(void);
void oled_display_WaterLevel(unsigned char index);
void oled_fill(void);
#endif  
	 



