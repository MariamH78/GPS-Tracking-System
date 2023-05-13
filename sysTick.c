#include "sysTick.h"
#include "TM4C1234.h"
#include "tm4c123gh6pm.h"

void systick_init(void){
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 0X00FFFFFF;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R = 0X05;
}
void delay_micro(int d){
	while(d--){
		NVIC_ST_RELOAD_R = 1600 - 1;
		NVIC_ST_CURRENT_R = 0;
		while((NVIC_ST_CTRL_R & 0X00010000) == 0);
	}
}
void delay_milli(int d){
	while(d--){
		NVIC_ST_RELOAD_R = 16000 - 1;
		NVIC_ST_CURRENT_R = 0;
		while((NVIC_ST_CTRL_R & 0X00010000) == 0);
	}
}