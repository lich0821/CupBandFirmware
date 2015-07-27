#ifndef __FRAME_H__
#define __FRAME_H__

#include <stdint.h>
#include <stdbool.h>

#define	FRAME_HEAD_1	0xAA
#define	FRAME_HEAD_2	0xAA
#define	FRAME_TAIL		0xF0
#define	FRAME_LENGTH	11

typedef struct
{
	uint8_t		BreathRate;
	uint8_t		BreathIntL;
	uint8_t		BreathIntS;
	uint8_t		BodyTemp[2];
	uint8_t		SleepPose;
	uint8_t		Battery;
}FrameDataTypeDef;

typedef struct 
{
	uint8_t 			FrameHead[2];
	uint8_t 			FrameAddr[4];
	FrameDataTypeDef 	FrameData;
	uint8_t				FrameCheck;
	uint8_t				FrameTail;
	uint8_t				UpDate;
}FrameTypeDef;

extern FrameTypeDef BleFrame;


void FrameInit(void);
uint8_t BCCCheck(uint8_t *buf, uint8_t len);

#endif

