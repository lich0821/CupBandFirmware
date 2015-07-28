#ifndef __FRAME_H__
#define __FRAME_H__

#include <stdint.h>
#include <stdbool.h>

#define	FRAME_HEAD_1	0x55
#define	FRAME_HEAD_2	0xAA
#define	FRAME_TAIL_1	0x0D
#define FRAME_TAIL_2	0x0A
#define	FRAME_LENGTH	14

typedef struct
{
	uint8_t 	Addr[4];
	uint8_t		Time[4];	//month, day, hour, minute
	uint8_t		BodyTemp[2];
	uint8_t		StepCount[3];
	uint8_t		Battery;
}FrameDataTypeDef;

typedef struct 
{
	uint8_t 			FrameHead[2];
	FrameDataTypeDef 	FrameData;
	uint8_t				FrameCheck;
	uint8_t				FrameTail[2];
//	uint8_t				UpDate;
}FrameTypeDef;

extern FrameTypeDef BleFrame;


void FrameInit(void);
uint8_t BCCCheck(uint8_t *buf, uint8_t len);

#endif

