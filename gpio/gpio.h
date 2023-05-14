#ifndef GPIO_HEADER
#define GPIO_HEADER

#include"TM4C123.h"

#define RED_LED 0
#define BLUE_LED 1
#define GREEN_LED 2

#define LED_ON 1
#define LED_OFF 0

void PortF_Init(void);
void SET_LED(unsigned char color,unsigned char state);

#endif
