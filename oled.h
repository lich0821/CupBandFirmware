

#ifndef __OLED_H
#define __OLED_H			  	 
#include "spi.h"

#define oled_site 0    //1=0.96;0=0.66

void oled_clear(void);     //��������
void oled_display_on(void);          //����oled
void oled_display_off(void);     //�ر�oled
void oled_set_pos(unsigned char x, unsigned char y); //�ƶ���
void oled_init(void);
void oled_display_16(unsigned char x,unsigned char y,unsigned char *data_s);   //16*16
void oled_display_8(unsigned char x,unsigned char y,unsigned char *data_s);    //8*16

void oled_display_1532(unsigned char x,unsigned char y,unsigned char data);
void oled_display_T(void);
void oled_display_816(unsigned char x,unsigned char y,unsigned char data);
void oled_display_1532num2(unsigned char x,unsigned char y,unsigned char num);   //��ʾ2������1532
void oled_display_816int16(uint8_t x,uint8_t y,short int num);
void oled_display_816num4(uint8_t x,uint8_t y,uint16_t num);                    //��ʾ��ȷ�����ݳ���
void oled_display_816ico(unsigned char x,unsigned char y,unsigned char data);//��ʾͼ��
void oled_display_816num2(unsigned char x,unsigned char y,unsigned char num);//��ʾ2������816
void oled_showstr(uint8_t x,uint8_t y,unsigned char *p);

void oled_display_Taiji(void);
void oled_display_WaterLevel(unsigned char index);
void oled_fill(void);
#endif  
	 



