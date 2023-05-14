#ifndef UART_HEADER
#define UART_HEADER

#include "tm4c123gh6pm.h"
#include "sysTick.h"

void UART1_init(void);
char UART1_read(void);

#endif
