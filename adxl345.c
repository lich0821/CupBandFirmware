#include "adxl345.h"
#include "math.h"   
#include "twi_master.h"

//////////////////////////////////////////////////////////////////////////////////
static uint8_t m_device_address = 0xA6; //!< Device address in bits [7:1]
//static uint8_t gsensorData[6];


bool adxl345_register_read(uint8_t register_address, uint8_t *destination, uint8_t number_of_bytes)
{
	bool transfer_succeeded;
	transfer_succeeded = twi_master_transfer(m_device_address, &register_address, 1, TWI_DONT_ISSUE_STOP);
	transfer_succeeded &= twi_master_transfer(m_device_address|TWI_READ_BIT, destination, number_of_bytes, TWI_ISSUE_STOP);
	return transfer_succeeded;	
}

bool adxl345_register_write(uint8_t register_address, uint8_t value)
{	
	uint8_t w2_data[2];

	w2_data[0] = register_address;
	w2_data[1] = value;
	return twi_master_transfer(m_device_address, w2_data, 2, TWI_ISSUE_STOP);	  
}


//��ʼ��ADXL345.
//����ֵ:0,��ʼ���ɹ�;1,��ʼ��ʧ��.
uint8_t ADXL345_Init(void)
{				  
	uint8_t tmp;
	adxl345_register_read(DEVICE_ID, &tmp, 1);
	if(tmp == 0XE5)	//��ȡ����ID
	{  
		adxl345_register_write(0x1E,0x00);   //????
		adxl345_register_write(0x1F,0x00);   //X ??? ????????????pdf29?
		adxl345_register_write(0x20,0x05);   //Y ??? ????????????pdf29?
		
		adxl345_register_write(0x1D,0x30);   //�������ٶȷ�ֵTHRESH_TAP  3g 62.5mg/LSB
		adxl345_register_write(0x21,0xa0);   //����ʱ��   DUR 100ms
		adxl345_register_write(0x22,0x30);  //������ʱʱ�� (1.25ms/LSB) ����֮��Xms �ٵ���latent 20ms
		adxl345_register_write(0x23,0xa0);  //window ����֮�� �ٴε���ʱ���� (1.25ms/LSB)window   320ms
	
		adxl345_register_write(0x24,0x10);  // (62.5mg/LSB)  ���ֵ
		adxl345_register_write(0x25,0X10);  // (62.5mg/LSB)  ��ֹ��ֵ
		adxl345_register_write(0x26,0x10);  // adxl��ֹ��ֵ (1s/LSB inactivity ʱ�䷧ֵ
		adxl345_register_write(0x27,0x0F);  ////������뾲ֹ �ж����� ��4λ��ж�  ����λ��ֹ�ж�
//		adxl345_register_write(0x28,0x09);  //�������巧ֵ (62.5mg/LSB)
//		adxl345_register_write(0x29,0xFF);  //�������ֵС��0x28 ��ʱ�䷧ֵ (5ms/LSB)
		adxl345_register_write(0x2A,0x02);  //�û�ʹ�� �ж����� ѡ���ж���  bit2=4
		adxl345_register_write(0x2C,0x08);  // 0x0A=100hz=10ms  09=50hz=20ms 08=25hz=40ms
		adxl345_register_write(0x2D,0x08);  //
	
		adxl345_register_write(0x2E,0x4A);  //INT->ENABLE  2-4
		adxl345_register_write(0x2F,0x68);  //�ж�pin INT->MAP Int1=0 Int2=1 
		 
		adxl345_register_write(0x31,0x2B);   ////???????,13?????,???????,16g?? 
		adxl345_register_write(0x38,0x9E);  //FIFO????,FIFO????32?????FIFO??????????????,31?????
		return 0;
	}			
	return 1;	   								  
}   

void ADXL345_RD_XYZ(uint8_t *buf)
{
	adxl345_register_read(DATA_X0, buf, 6);
}

int16_t ADXL345_GetAngle(uint8_t *gsensorData)
{
	int16_t angle;
	float tmp;
//	int16_t x;
	int16_t	y, z;
//	uint16_t ax;
	uint16_t ay, az;
//	adxl345_register_read(DATA_X0, gsensorData, 6);
	
//	ax = gsensorData[0] + ((uint16_t)gsensorData[1] << 8);
	ay = gsensorData[2] + ((uint16_t)gsensorData[3] << 8);
	az = gsensorData[4] + ((uint16_t)gsensorData[5] << 8);	

//	x = ax < 32768 ? ax : ax-65536;
	y = ay < 32768 ? ay : ay-65536;
	z = az < 32768 ? az : az-65536;		
	
	tmp = atan2(z, -y);
	tmp *= 180/PI;
	angle = (int16_t) tmp;
	
	return angle;
}
signed char getWaterLevel(uint8_t *gsensorData)
{
	signed char waterLevel = -100;
	int16_t y, z;
	uint16_t ay, az;
	//	adxl345_register_read(DATA_X0, gsensorData, 6);

	//ax = gsensorData[0] + ((uint16_t)gsensorData[1] << 8);
	ay = gsensorData[2] + ((uint16_t)gsensorData[3] << 8);
	az = gsensorData[4] + ((uint16_t)gsensorData[5] << 8);	

	//x = ax < 32768 ? ax : ax-65536;
	y = ay < 32768 ? ay : ay-65536;
	z = az < 32768 ? az : az-65536;	
	
	waterLevel = (-100*y / sqrt(y*y + z*z) + 5) / 10;
	
	return waterLevel;
}
