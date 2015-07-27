#ifndef __PEDOMETER_H__
#define __PEDOMETER_H__

#include <stdint.h>
#include "mma8451.h"

extern uint8_t Interval;
extern uint32_t STEPS;

void stepCounter(void);


#endif

