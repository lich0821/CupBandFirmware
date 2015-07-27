#include "frame.h"
#include "string.h"

FrameTypeDef BleFrame;


void FrameInit(void)
{
	memset(&BleFrame, 0, sizeof(BleFrame));
	
	BleFrame.FrameHead[0]	= FRAME_HEAD_1;
	BleFrame.FrameHead[1]	= FRAME_HEAD_2;
	BleFrame.FrameAddr[0]	= 0x12;	//read from flash
	BleFrame.FrameAddr[1]	= 0x34;
	BleFrame.FrameAddr[2]	= 0x56;
	BleFrame.FrameAddr[3]	= 0x78;
	BleFrame.FrameData.BreathIntL	= 0x00;
	BleFrame.FrameData.BreathIntS	= 0xFF;
	BleFrame.FrameTail		= FRAME_TAIL;
}

uint8_t BCCCheck(uint8_t *buf, uint8_t len)
{
	uint8_t i;
	uint8_t checksum=0;
	
	for(i=0;i<len;i++)
	{
		checksum ^= *buf++;
	}
	
	return checksum;
}



