#include "sysTick.h"
#include "lcd.h"
#include "gps.h"
#include "UART.h"
#include "gpio/gpio.h"
#include "gpio/distance.h"

int main(void){
	char lat[12], lon[12], dist[12], toggle_clear = 1;
	position coords;
	double distance_double;
	
	systick_init();
	UART1_init();
	LCD_INIT();
	PortF_Init();
	
	SET_LED(RED_LED, LED_ON);
		
	while(1){
		coords.lon_exists = 0;
		coords.lat_exists = 0;
			
		filter_data(&coords);

		if (coords.lat_exists && coords.lon_exists){
			ftoa(coords.latitude, lat);
			ftoa(coords.longitude, lon);
			
			distance_double = distance(coords.latitude, coords.longitude, TARGET_LAT, TARGET_LON);
			ftoa(distance_double, dist);
			
			if (toggle_clear) {
				LCD_CMD(0X01);
				toggle_clear = 0;
			}
			
			if (distance_double <= 1){
				SET_LED(RED_LED, LED_OFF);
				SET_LED(GREEN_LED, LED_ON);
			} else if (distance_double <= 5){
				SET_LED(GREEN_LED, LED_OFF);
				SET_LED(RED_LED, LED_ON);
			} else {
				SET_LED(GREEN_LED, LED_OFF);
				SET_LED(RED_LED, LED_ON);
			}
			
			LCD_write_coords(lat, lon, dist);
						
		} else {
			if (!toggle_clear){
				LCD_CMD(0X01);
				toggle_clear = 1;
			}
			
			LCD_CMD(0X0E); //cursor
			LCD_CMD(0X81); //FIRST LINE, SECOND LETTER
			LCD_write_string("Fix not found!");
			
			//LCD_write_coords("30.0332", "31.14570", "200.5436"); //TESTING ONLY
		}
		
	}
	
	return 0;
}







