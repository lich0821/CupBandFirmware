#include"spi.h"

void spi_pin_init(void)
{
	nrf_gpio_cfg_output(spi_sck);      //推挽输出
	nrf_gpio_cfg_output(spi_mosi);    //推挽输出
	nrf_gpio_cfg_output(spi_miso);    //推挽输出
	//nrf_gpio_cfg_input(spi_miso,GPIO_PIN_CNF_PULL_Pullup);//设置管脚位上拉输入
	nrf_gpio_cfg_output(oled_cs);     //推挽输出
	nrf_gpio_cfg_output(oled_rst);   //推挽输出

	nrf_gpio_pin_set(oled_cs);
}

void spi_r_datcmd(uint8_t dat,uint8_t cmd)     //spi写cmd:0命令 1：数据
{	
	uint8_t i;			 //data接受数据 
	if(cmd)
		OLED_DC_Set();    //命令  dc=1
	else 
		OLED_DC_Clr();		  //数据  dc=0
	OLED_CS_Clr();         //片选 cs=0
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();       //clk=0   时钟
		if(dat&0x80)
			OLED_SDIN_Set();
		else
			OLED_SDIN_Clr();
		OLED_SCLK_Set();       //clk=1
		dat<<=1;
	}				 		  
	OLED_CS_Set();          //片选cs=1
	OLED_DC_Set();   	       //dc=1
} 
uint8_t spi_rw(uint8_t dat)     //spi读写
{	
	uint8_t i,data;			 //data接受数据 
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();       //clk=0   时钟

		if(dat&0x80)
			OLED_SDIN_Set();
		else
			OLED_SDIN_Clr();		

		OLED_SCLK_Set();       //clk=1
		dat<<=1;            //发送数据进行移位

		data<<=1;           //接收数据进行移位
		data|=spi_mosi_in;
	}				 		  	
	return data;
} 
 
