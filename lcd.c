#include "lcd.h"
#include "TM4C1234.h"
#include "tm4c123gh6pm.h"
#include "sysTick.h"

void LCD_INIT(void) {
	SYSCTL_RCGCGPIO_R |=0x03;
	while((SYSCTL_PRGPIO_R & 0x03) ==0);
	
	GPIO_PORTB_AFSEL_R &= ~0xff;    //disable alternative functions for portB
	GPIO_PORTB_AMSEL_R &= ~0Xff;    //disable analogue function
	GPIO_PORTB_PCTL_R &= ~0XFF;     //regular digital pins
	GPIO_PORTB_DIR_R  |= 0XFF;      //set the direction of PB0-7 as output
	GPIO_PORTB_DEN_R  |= 0XFF;      //enable digital portB

	// PA5 >> r/w, PA6 >> EN, PA7 >> RS
	GPIO_PORTA_AFSEL_R &= ~0xE0;    //disable alternative functions for PA5,6,7
	GPIO_PORTA_AMSEL_R &= ~0XE0;    //disable analogue function for PA5,6,7
	GPIO_PORTA_PCTL_R &= ~0XE0;     //regular digital pins
	GPIO_PORTA_DIR_R |= 0XE0;       //set the direction of PA5,6,7 as output
	GPIO_PORTA_DEN_R |= 0XE0;       //enable digital PA5,6,7


	//LCD_CMD(0x38); //Function_set_8bit
	delay_milli(500);
	LCD_CMD(0x3C);  /*Function set 8-bit, and Set 5x7 font size*/
	delay_milli(5);
	LCD_CMD(0x3C);  /*Do it again to enable second line of the display*/
	delay_milli(5);
	LCD_CMD(0x06); /*Automatically increment cursor right */
	delay_milli(5);
	LCD_CMD(0x01); /*clear display*/
	delay_milli(5);
	LCD_CMD(0x0E);  /*Enable Display and cursor blinking */
	delay_milli(1000);
}

void LCD_CMD(unsigned long cmd) {
	GPIO_PORTB_DATA_R = cmd;    //set PB7-0 as the passed command to the function
	low_rs  						//set PA7 register select pin to low
	low_rw  						//set PA5 r/w pin to low
	high_en  						//set enable pin to high
	delay_micro(250);        						//short delay 
	low_en  						//set enable pin to low 
	delay_milli(3);
}
void LCD_WRITE (char data ) {
	GPIO_PORTB_DATA_R = data;  //write the data to PB7-0
	high_rs  					 //set PA7 to high
	low_rw  					 //set pA5 to low
	high_en  					 //set the enable pin high
	delay_micro(250);       					 //short delay 
	low_en  					 //set the enable pin to low
	delay_milli(1);
}
void LCD_write_coords(char* lat, char* lon){
	LCD_CMD(0x80); //first line
	LCD_write_string("Lat: ");
	LCD_write_string(lat);
	
	LCD_CMD(0XA8); //second line
	LCD_write_string("Lon: ");
	LCD_write_string(lon);
	delay_milli(3);
}
void LCD_write_string(char* data){
	int i = 0;
	while (data[i]){
		LCD_WRITE(data[i++]);
	}
}
