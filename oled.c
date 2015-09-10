#include "oled.h"  	 
#include "font.h"
#include "nrf_delay.h"

#if oled_site
void oled_set_pos(unsigned char x, unsigned char y) //ÒÆ¶¯µã
{ 
	spi_r_datcmd(0xb0+y,OLED_CMD);
	spi_r_datcmd(((x&0xf0)>>4)|0x10,OLED_CMD);
	spi_r_datcmd((x&0x0f)|0x01,OLED_CMD); 
}
#else
 void oled_set_pos(unsigned char x, unsigned char y) 
{ 
	spi_r_datcmd(0xb2+y,OLED_CMD);
	spi_r_datcmd((((x+0x20)&0xf0)>>4)|0x10,OLED_CMD);
	spi_r_datcmd((x&0x0f)|0x01,OLED_CMD); 
} 
#endif
void oled_display_on(void)          //¿ªÆôoled
{
	spi_r_datcmd(0X8D,OLED_CMD);  //SET DCDC??
	spi_r_datcmd(0X14,OLED_CMD);  //DCDC ON
	spi_r_datcmd(0XAF,OLED_CMD);  //DISPLAY ON
}   
void oled_display_off(void)     //¹Ø±Õoled
{
	spi_r_datcmd(0X8D,OLED_CMD);  //SET DCDC??
	spi_r_datcmd(0X10,OLED_CMD);  //DCDC OFF
	spi_r_datcmd(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			  
void oled_clear(void)     //ÇåÆÁº¯Êý
{  
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		spi_r_datcmd (0xb0+i,OLED_CMD);    //?????(0~7)
		spi_r_datcmd (0x00,OLED_CMD);      //??????—????
		spi_r_datcmd (0x10,OLED_CMD);      //??????—????   
		for(n=0;n<128;n++)spi_r_datcmd(0,OLED_DATA); 
	}  
}	
void oled_fill(void)     //ÆÁº¯Êý
{  
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		spi_r_datcmd (0xb0+i,OLED_CMD);    //?????(0~7)
		spi_r_datcmd (0x00,OLED_CMD);      //??????—????
		spi_r_datcmd (0x10,OLED_CMD);      //??????—????
		//if(i % 2 == 0)
			for(n=0;n<128;n++)spi_r_datcmd(0xFF,OLED_DATA); 
	}
}	
void oled_init(void)
{

	OLED_RST_Set();
	nrf_delay_ms(100);
	OLED_RST_Clr();
	nrf_delay_ms(100);
	OLED_RST_Set(); 

	spi_r_datcmd(0xAE,OLED_CMD);//--turn off oled panel
	spi_r_datcmd(0x00,OLED_CMD);//---set low column address
	spi_r_datcmd(0x10,OLED_CMD);//---set high column address
	spi_r_datcmd(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	spi_r_datcmd(0x81,OLED_CMD);//--set contrast control register
	spi_r_datcmd(0xCF,OLED_CMD); // Set SEG Output Current Brightness
	spi_r_datcmd(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0???? 0xa1??
	spi_r_datcmd(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0???? 0xc8??
	spi_r_datcmd(0xA6,OLED_CMD);//--set normal display
	spi_r_datcmd(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	spi_r_datcmd(0x3f,OLED_CMD);//--1/64 duty
	spi_r_datcmd(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	spi_r_datcmd(0x00,OLED_CMD);//-not offset
	spi_r_datcmd(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	spi_r_datcmd(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	spi_r_datcmd(0xD9,OLED_CMD);//--set pre-charge period
	spi_r_datcmd(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	spi_r_datcmd(0xDA,OLED_CMD);//--set com pins hardware configuration
	spi_r_datcmd(0x12,OLED_CMD);
	spi_r_datcmd(0xDB,OLED_CMD);//--set vcomh
	spi_r_datcmd(0x40,OLED_CMD);//Set VCOM Deselect Level
	spi_r_datcmd(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	spi_r_datcmd(0x02,OLED_CMD);//
	spi_r_datcmd(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	spi_r_datcmd(0x14,OLED_CMD);//--set(0x10) disable
	spi_r_datcmd(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	spi_r_datcmd(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	spi_r_datcmd(0xAF,OLED_CMD);//--turn on oled panel
	
	spi_r_datcmd(0xAF,OLED_CMD); /*display ON*/ 
	 oled_clear();
 
}  

void writedata(unsigned char datatowrite)//Ð´Êý¾Ý
{
  spi_r_datcmd(datatowrite,1);
}
void oled_display_16(unsigned char x,unsigned char y,unsigned char *data_s)
{  //16*16
	unsigned char i;
	oled_set_pos(x*16,y*2);
	for(i=0;i<16;i++)
	{    
		writedata(data_s[i]);
	}
	oled_set_pos(x*16,y*2+1);
	for(i=0;i<16;i++)
	{    
		writedata(data_s[i+16]);
	}
	writedata(0);
}
void oled_display_8(unsigned char x,unsigned char y,unsigned char *data_s)
{  //8*16
	unsigned char i;
	oled_set_pos(x*8,y*2);
	for(i=0;i<8;i++)
	{    
		writedata(data_s[i]);
	}
	oled_set_pos(x*8,y*2+1);
	for(i=0;i<8;i++)
	{    
		writedata(data_s[i+8]);
	}
	writedata(0);
}
void oled_display_816(unsigned char x,unsigned char y,unsigned char data)
{  //8*16
	unsigned char i;
	oled_set_pos(x*8,y*2);
	//	data-=0x30;
	for(i=0;i<8;i++)
	{    
		writedata(font_816[data][i]);
	}
	oled_set_pos(x*8,y*2+1);
	for(i=0;i<8;i++)
	{    
		writedata(font_816[data][i+8]);
	}
	writedata(0);
}
void oled_display_816ico(unsigned char x,unsigned char y,unsigned char data)
{  //8*16
	unsigned char i;
	oled_set_pos(x*8,y*2);
	//	data-=0x30;
	for(i=0;i<8;i++)
	{    
		writedata(ico_816[data][i]);
	}
	oled_set_pos(x*8,y*2+1);
	for(i=0;i<8;i++)
	{    
		writedata(ico_816[data][i+8]);
	}
	writedata(0);
}

void oled_display_Taiji(void)
{  //48*48
	unsigned char i;
	unsigned char y;
	
	for(y=0;y<6;y++)
	{
		oled_set_pos(8, y);
		for(i=0;i<48;i++)
		{    
			writedata(taiji[y*48+i]);
		}	
	}
}

void oled_display_WaterLevel(unsigned char index)
{  //48*48
	unsigned char i;
	unsigned char y;
	
	for(y=0;y<6;y++)
	{
		oled_set_pos(8, y);
		for(i=0;i<48;i++)
		{    
			writedata(WaterLevel[index][y*48+i]);
		}	
	}
}

void oled_display_T(void)
{  
	unsigned char i;
	oled_set_pos(32,3);
	for(i=0;i<2;i++)
	{    
		writedata(0x18);
	}
	oled_set_pos(32,4);
	for(i=0;i<2;i++)
	{    
		writedata(0x18);
	}
	writedata(0);
}
void oled_display_1532(unsigned char x,unsigned char y,unsigned char data)
{   
	unsigned char i;
	oled_set_pos(x,y);
	for(i=0;i<15;i++)   //8*24
	{    
		writedata(font_1532[data][i]);
	}
	oled_set_pos(x,y+1);
	for(i=0;i<15;i++)  //8*24
	{    
		writedata(font_1532[data][i+15]);
	}
	oled_set_pos(x,y+2);  //8*24
	for(i=0;i<15;i++)
	{    
		writedata(font_1532[data][i+30]);
	}
	oled_set_pos(x,y+3);   //8*24
	for(i=0;i<15;i++)       
	{    
		writedata(font_1532[data][i+45]);
	}
	writedata(0);
}

void oled_display_816int16(uint8_t x,uint8_t y,short int num)    //ÏÔÊ¾
{	
	short int tmp;
	uint8_t i, negative=0, len=1;
	
	if(num < 0)
	{
		negative = 1;
		len = 2;
		num = -num;
	}
	tmp = num;
	
	for(i=0;i<10;i++) //
	{
		num/=10;     //¼õÐ¡Ò»Î»
		if(num>0)
		{   
			len++;           //Êý×Ö³¤¶È¼ÓÒ»
		}
		else
			break;  //Ìø³öfor
	}

	for(i=0;i<len;i++)
	{
		oled_display_816(x+len-i,y,tmp%10);//ÏÔÊ¾×îºóÒ»Î»
		tmp /= 10;  //¼õ³ý×îºóÒ»Î»
		if(tmp == 0)
		{
			if(negative == 1)
			{
				oled_display_816(x+len-i-1,y,10);//ÏÔÊ¾-
			}
			break;
		}
			
	}
}


void oled_display_816num4(uint8_t x,uint8_t y,uint16_t num)    //ÏÔÊ¾²½Êý
{	
	uint16_t j;
	uint8_t i,len=1;
	j=num;
	for(i=0;i<10;i++) //
	{
		num/=10;     //¼õÐ¡Ò»Î»
		 if(num>0)
		 {   
			 len++;           //Êý×Ö³¤¶È¼ÓÒ»
		 }
		 else
			 break;  //Ìø³öfor
	}
	for(i=0;i<len;i++)
	{
		oled_display_816(x+len-i,y,j%10);//ÏÔÊ¾×îºóÒ»Î»
		j/=10;  //¼õ³ý×îºóÒ»Î»
		if(j==0)
			break;
	}
}
void oled_display_816num2(unsigned char x,unsigned char y,unsigned char num)
{  
	oled_display_816(x,y,num/10);
	oled_display_816(x+1,y,num%10);
}
void oled_display_1532num2(unsigned char x,unsigned char y,unsigned char num)
{//x=0»ò15   
  oled_display_1532(x,y,num/10);
	oled_display_1532(x+15,y,num%10);
}
void oled_display_str(unsigned char x,unsigned char y,unsigned char data)
{  //8*16
	unsigned char i;
	oled_set_pos(x*8,y*2);
	data=data-' ';//Æ«ÒÆÖµ
	for(i=0;i<8;i++)
	{    
		writedata(oled_asc_816[data][i]);
	}
	oled_set_pos(x*8,y*2+1);
	for(i=0;i<8;i++)
	{    
		writedata(oled_asc_816[data][i+8]);
	}
	writedata(0);
}
void oled_showstr(uint8_t x,uint8_t y,unsigned char *p)
{        
    while(*p!='\0')
    { 
        if(x>7){x=0;y+=1;}
        if(y>3){y=x=0;oled_clear();}
        oled_display_str(x,y,*p);	 
        x+=1;
        p++;
    }  
}

