#include"TM4C123.h"
#include"GPIo.h"

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

// Port D init
void PortD_Init(void){ 
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3;
  while ((SYSCTL_PRGPIO_R&SYSCTL_RCGCGPIO_R3)==0) ; 
  GPIO_PORTD_LOCK_R = 0x4C4F434B;   // Unlock PortF PF0  
  GPIO_PORTD_CR_R = 0xFF;           // Allow changes to PF4-0       
  GPIO_PORTD_AMSEL_R = 0x00;        // Disable analog function
  GPIO_PORTD_PCTL_R = 0x00000000;   // GPIO clear bit PCTL  
  GPIO_PORTD_DIR_R = 0xFF;          // PF4,PF0 input, PF3,PF2,PF1 output   
  GPIO_PORTD_AFSEL_R = 0x00;        // No alternate function
  GPIO_PORTD_PUR_R = 0x00;          // Enable pullup resistors on PF4,PF0       
  GPIO_PORTD_DEN_R = 0xFF;          // Enable digital pins PF4-PF0        
}
// Port B init
void PortB_Init(void){ 
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
  while ((SYSCTL_PRGPIO_R&SYSCTL_RCGCGPIO_R1)==0)  ; 
  GPIO_PORTB_LOCK_R = 0x4C4F434B;   // Unlock PortF PF0  
  GPIO_PORTB_CR_R = 0xFF;           // Allow changes to PF4-0       
  GPIO_PORTB_AMSEL_R = 0x00;        // Disable analog function
  GPIO_PORTB_PCTL_R = 0x00000000;   // GPIO clear bit PCTL  
  GPIO_PORTB_DIR_R = 0xFF;          // PF4,PF0 input, PF3,PF2,PF1 output   
  GPIO_PORTB_AFSEL_R = 0x00;        // No alternate function
  GPIO_PORTB_PUR_R = 0x00;          // Enable pullup resistors on PF4,PF0       
  GPIO_PORTB_DEN_R = 0xFF;          // Enable digital pins PF4-PF0      
}

unsigned char sw_value(unsigned char sw){
switch (sw)
{
case 0:return GPIO_PORTF_DATA_R &0x010 ;          // value of sw01
break;
case 1:return GPIO_PORTF_DATA_R &0x01;            // value of sw02
break;
default: return 0;
  break;
}


}

void SET_LED(unsigned char color,unsigned char state){                // 1st Para FOR color 2nd for state on/of
switch (color)
{
case RED_LED :
switch (state)
{
case LED_ON : GPIO_PORTF_DATA_R |=0x02;
  break;
case LED_OF : GPIO_PORTF_DATA_R &=~0x02;
  break;
default:break;
}
break;
  case BLUE_LED :
switch (state)
{
case LED_ON : GPIO_PORTF_DATA_R |=0x04;
  break;
case LED_OF : GPIO_PORTF_DATA_R &=~0x04;
  break;
default:break;
}
break;
case GREEN_LED :
switch (state)
{
case LED_ON : GPIO_PORTF_DATA_R |=0x08;
  break;
case LED_OF : GPIO_PORTF_DATA_R &=~0x08;
  break;
default:
  break;
}
  

default : break;


}


}



