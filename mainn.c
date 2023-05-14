#include "sysTick.h"
#include "lcd.h"
#include "gps.h"
#include "UART.h"

int main(void){
	char lat[12], lon[12], toggle_clear = 1;
	position coords;
	//double distance_double;
	//char distance_string[15];
	systick_init();
	UART1_init();
	LCD_INIT();

	while(1){
		coords.lon_exists = 0;
		coords.lat_exists = 0;
			
		filter_data(&coords);

		if (coords.lat_exists && coords.lon_exists){
			ftoa(coords.latitude, lat);
			ftoa(coords.longitude, lon);
			if (toggle_clear) {
				LCD_CMD(0X01);
				toggle_clear = 0;
			}
			LCD_write_coords(lat, lon);

		} else {
			if (!toggle_clear){
				LCD_CMD(0X01);
				toggle_clear = 1;
			}
			
			LCD_CMD(0X0E); //cursor
			LCD_CMD(0X81); //FIRST LINE, SECOND LETTER
			LCD_write_string("Fix not found!");
			
			//LCD_write_coords("30.0332", "31.14570"); //TESTING ONLY
		}
		
	}
	
	return 0;
}







