#ifndef __SPI_H
#define	__SPI_H

//#include "delay.h"
#include <stdint.h>
#include "nrf_gpio.h"

#define spi_sck          19
#define spi_mosi          18
#define spi_miso          17
#define oled_cs         25            //�������
#define oled_rst         22


#define OLED_CMD  0	//???
#define OLED_DATA 1	//???
#define OLED_MODE 0

#define OLED_CS_Clr()  nrf_gpio_pin_clear(oled_cs)       //spiƬѡ
#define OLED_CS_Set()  nrf_gpio_pin_set(oled_cs) 

#define OLED_RST_Clr() nrf_gpio_pin_clear(oled_rst)      //oled��λ�ź�
#define OLED_RST_Set() nrf_gpio_pin_set(oled_rst) 

#define OLED_DC_Clr() nrf_gpio_pin_clear(spi_miso)       //��������
#define OLED_DC_Set() nrf_gpio_pin_set(spi_miso) 

#define OLED_SCLK_Clr() nrf_gpio_pin_clear(spi_sck)     //ʱ���ź�
#define OLED_SCLK_Set() nrf_gpio_pin_set(spi_sck) 

#define OLED_SDIN_Clr() nrf_gpio_pin_clear(spi_mosi)   //�������
#define OLED_SDIN_Set() nrf_gpio_pin_set(spi_mosi) 

#define spi_mosi_in   ((NRF_GPIO->IN >> spi_miso) & 0x1UL)        //����spi_miso

#define spi_mosi_pin_in()  do { NRF_GPIO->DIRCLR = (1UL << spi_miso);  } while(0)   /*!< Configures SDA pin as input  */
#define spi_mosi_pin_out() do { NRF_GPIO->DIRSET = (1UL << spi_miso);  } while(0)   /*!< Configures SDA pin as output */


void spi_pin_init(void);
void spi_r_datcmd(uint8_t dat, uint8_t cmd); //spiдcmd:0���� 1������
uint8_t spi_rw(uint8_t dat);     //spi��д
#endif /* __spi_H */

