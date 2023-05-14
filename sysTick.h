#ifndef SYSTICK_HEADER
#define SYSTICK_HEADER

#include "tm4c123gh6pm.h"

void systick_init(void);
void delay_milli(int d);
void delay_micro(int d);

#endif
