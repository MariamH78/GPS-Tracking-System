#ifndef LCD_HEADER
#define LCD_HEADER

#include "tm4c123gh6pm.h"

#define low_rs GPIO_PORTA_DATA_R &= ~(1 << 7);
#define high_rs GPIO_PORTA_DATA_R |= (1 << 7);

#define low_en GPIO_PORTA_DATA_R &= ~(1 << 6);
#define high_en GPIO_PORTA_DATA_R |= (1 << 6);

#define low_rw GPIO_PORTA_DATA_R &= ~(1 << 5);
#define high_rw GPIO_PORTA_DATA_R |= (1 << 5);

void LCD_CMD(unsigned long cmd);
void LCD_WRITE (char data );
void LCD_INIT(void);
void LCD_write_string(char* data);
void LCD_write_coords(char* lat, char* lon);

#endif

