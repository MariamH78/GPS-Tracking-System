#include "gpio.h"

// Port F init
void PortF_Init(void){ 
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
  while ((SYSCTL_PRGPIO_R&SYSCTL_RCGCGPIO_R5)==0);
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // Unlock PortF PF0  
  GPIO_PORTF_CR_R = 0x1F;           // Allow changes to PF4-0       
  GPIO_PORTF_AMSEL_R = 0x00;        // Disable analog function
  GPIO_PORTF_PCTL_R = 0x00000000;   // GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R = 0x0E;          // PF4,PF0 input, PF3,PF2,PF1 output   
  GPIO_PORTF_AFSEL_R = 0x00;        // No alternate function
  GPIO_PORTF_PUR_R = 0x11;          // Enable pullup resistors on PF4,PF0       
  GPIO_PORTF_DEN_R = 0x1F;          // Enable digital pins PF4-PF0    
  GPIO_PORTF_DATA_R&=~0x0E;         //init the leds
}


void SET_LED(unsigned char color,unsigned char state){                // 1st Para FOR color 2nd for state on/of
	switch (color)
	{
		case RED_LED:
			switch (state)
			{
				case LED_ON :
					GPIO_PORTF_DATA_R |=0x02;
					break;
				case LED_OFF:
					GPIO_PORTF_DATA_R &=~0x02;
					break;
				default:
				break;
			}
			break;
		
		case BLUE_LED:
			switch (state)
			{
				case LED_ON :
					GPIO_PORTF_DATA_R |=0x04;
					break;
				case LED_OFF:
					GPIO_PORTF_DATA_R &=~0x04;
					break;
				default:
					break;
			}
			break;
			
		case GREEN_LED:
			switch (state)
			{
			case LED_ON:
				GPIO_PORTF_DATA_R |=0x08;
				break;
			case LED_OFF:
				GPIO_PORTF_DATA_R &=~0x08;
				break;
			default:
				break;
			}
			break;
		
		default:
			break;
	}
}



