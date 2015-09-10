#include"spi.h"

void spi_pin_init(void)
{
	nrf_gpio_cfg_output(spi_sck);      //�������
	nrf_gpio_cfg_output(spi_mosi);    //�������
	nrf_gpio_cfg_output(spi_miso);    //�������
	//nrf_gpio_cfg_input(spi_miso,GPIO_PIN_CNF_PULL_Pullup);//���ùܽ�λ��������
	nrf_gpio_cfg_output(oled_cs);     //�������
	nrf_gpio_cfg_output(oled_rst);   //�������

	nrf_gpio_pin_set(oled_cs);
}

void spi_r_datcmd(uint8_t dat,uint8_t cmd)     //spiдcmd:0���� 1������
{	
	uint8_t i;			 //data�������� 
	if(cmd)
		OLED_DC_Set();    //����  dc=1
	else 
		OLED_DC_Clr();		  //����  dc=0
	OLED_CS_Clr();         //Ƭѡ cs=0
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();       //clk=0   ʱ��
		if(dat&0x80)
			OLED_SDIN_Set();
		else
			OLED_SDIN_Clr();
		OLED_SCLK_Set();       //clk=1
		dat<<=1;
	}				 		  
	OLED_CS_Set();          //Ƭѡcs=1
	OLED_DC_Set();   	       //dc=1
} 
uint8_t spi_rw(uint8_t dat)     //spi��д
{	
	uint8_t i,data;			 //data�������� 
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();       //clk=0   ʱ��

		if(dat&0x80)
			OLED_SDIN_Set();
		else
			OLED_SDIN_Clr();		

		OLED_SCLK_Set();       //clk=1
		dat<<=1;            //�������ݽ�����λ

		data<<=1;           //�������ݽ�����λ
		data|=spi_mosi_in;
	}				 		  	
	return data;
} 
 
