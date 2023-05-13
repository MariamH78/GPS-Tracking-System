#include "TM4C1234.h"
#include <stdlib.h>
#include "lcd.h"
#include "sysTick.h"
#include "gps.h"
#include "UART.h"

int main(void){
	char lat[15], lon[15], toggle_clear = 1;
	int size;
	position coords;
	//double distance_double;
	//char distance_string[15];
	systick_init();
	UART1_init();
	LCD_INIT();
	PortD_Init;
                PortF_Init;
                PortB_Init;
	while(1){
		 
		char data[100] = {0};
		size = filter_data(data);
		coords = get_pose_from_filtered_data(data, size);
		if (coords.lat_exists && coords.lon_exists){
			ftoa(coords.latitude, lat);
			ftoa(coords.longitude, lon);
			if (toggle_clear) {
				LCD_CMD(0X01);
				toggle_clear = 0;
			}
			LCD_write_coords(lat, lon);
			/* if  (DIS =0 ) { 
        set_led (green_led , led_on ) ; 
        elseif (DIS <= 5 )  
            set_led (red_led , led_on);
	else 
		set_led (yellow_led , led_on); 
			/* TODO:
			* distance = get_distance(coords);
			* ftoa(distance_double, distance_string);
			* implement double get_distance(position current_pose)
			* define target pose in header defines
			*/
		} */ 
		else {
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








