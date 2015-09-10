#ifndef __ADXL345_H
#define __ADXL345_H 												  	  
#include <stdint.h>

#define DEVICE_ID		0X00 	//����ID,0XE5
#define THRESH_TAP		0X1D   	//�û���ֵ
#define OFSX			0X1E
#define OFSY			0X1F
#define OFSZ			0X20
#define DUR				0X21
#define Latent			0X22
#define Window  		0X23 
#define THRESH_ACK		0X24
#define THRESH_INACT	0X25 
#define TIME_INACT		0X26
#define ACT_INACT_CTL	0X27	 
#define THRESH_FF		0X28	
#define TIME_FF			0X29 
#define TAP_AXES		0X2A  
#define ACT_TAP_STATUS  0X2B 
#define BW_RATE			0X2C 
#define POWER_CTL		0X2D 

#define INT_ENABLE		0X2E
#define INT_MAP			0X2F
#define INT_SOURCE  	0X30
#define DATA_FORMAT	    0X31
#define DATA_X0			0X32
#define DATA_X1			0X33
#define DATA_Y0			0X34
#define DATA_Y1			0X35
#define DATA_Z0			0X36
#define DATA_Z1			0X37
#define FIFO_CTL		0X38
#define FIFO_STATUS		0X39

 
#define PI				3.141592654 
 
//���ALT ADDRESS��(12��)�ӵ�,IIC��ַΪ0X53(���������λ).
//�����V3.3,��IIC��ַΪ0X1D(���������λ).
//��Ϊ�������V3.3,����תΪ��д��ַ��,Ϊ0X3B��0X3A(�����GND,��Ϊ0XA7��0XA6)  
#define ADXL_READ    0XA7
#define ADXL_WRITE   0XA6

uint8_t ADXL345_Init(void);						//��ʼ��ADXL345
void ADXL345_WR_Reg(uint8_t addr,uint8_t val);	//дADXL345�Ĵ���
uint8_t ADXL345_RD_Reg(uint8_t addr);			//��ADXL345�Ĵ���
void ADXL345_RD_XYZ(uint8_t *buf);				//��ȡһ��ֵ
int16_t ADXL345_GetAngle(uint8_t *gsensorData);
signed char getWaterLevel(uint8_t *gsensorData);
#endif

