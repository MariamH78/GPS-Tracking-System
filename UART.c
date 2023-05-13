#include "UART.h"
#include "TM4C1234.h"
#include "tm4c123gh6pm.h"
#include "sysTick.h"
void UART1_init(void){            // should be called only once
	SYSCTL_RCGCUART_R |= 0x0002;  // activate UART1
	delay_milli(1000);
  SYSCTL_RCGCGPIO_R |= 0x0004;  // activate port C
  UART1_CTL_R &= (unsigned long) ~0x0001;    // disable UART
  UART1_IBRD_R = 104;     // IBRD = int(80,000,000/(16*115,200)) = int(43.40278) was 26
  UART1_FBRD_R = 11;     // FBRD = round(0.40278 * 64) = 26 was 3
  UART1_LCRH_R = 0x0060;  // 8 bit, no parity bits, one stop, FIFOs
  UART1_CTL_R |= 0x0001;     // enable UART, used to be 0001
  GPIO_PORTC_AFSEL_R |= 0x30;    // enable alt funct on PC5-4
  GPIO_PORTC_DEN_R |= 0x30;      // configure PC5-4 as UART1
  GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFF00FFFF)+0x00220000;
  GPIO_PORTC_AMSEL_R &= (unsigned long) ~0x30;   // disable analog on PC5-4
}
char UART1_read(void){
  while((UART1_FR_R&0x0010) != 0);      // wait until RXFE is 0
  return((char)(UART1_DR_R&0xFF));
}