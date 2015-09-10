#ifndef	__CONFIG_H__
#define	__CONFIG_H__

#include "stdint.h"


#define CPU_LITTLE_ENDIAN		1

#ifdef CPU_LITTLE_ENDIAN	//Little-Endian
typedef	struct
{
	uint8_t	L;
	uint8_t H;
}LH_t;

#else	//Big-Endian

typedef	struct
{
	uint8_t	H;
	uint8_t L;
}LH_t;

#endif

typedef	union
{
	LH_t		Reg;
	uint16_t	u16Val;
}L2B_t;







#endif


