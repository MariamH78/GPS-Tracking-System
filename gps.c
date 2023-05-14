#include "gps.h"

void filter_data(position* current_pose) {
	int lat_size = 0, lon_size = 0, comma_counter = 0;
	char got_lat = 0, got_lon = 0, flag = 0;
	double input = 0, deg;
    
	char d = UART1_read();
	while (d != '$')
		d = UART1_read();

	double index = 10;
	while (d != '*') {
		
		switch (comma_counter){
			case 2:
                if (lat_size == 2){
                    deg = input;
                    input = 0;
                }
                lat_size++;

                if (d == ',')
                    break;
                if (d == '.') {
                    flag = 1;
                    break;
                }
                if (!flag) input = input*10 + (int)d - 48;
                else {
                    input = input + (((int)d - 48)/(index));
                    index *= 10;
                }

                break;
			case 3:
			    if (!got_lat){
                    got_lat = 1;
                    index = 0;
                    if (lat_size > 1){
                        current_pose -> lat_exists = 1;
                        current_pose -> latitude = deg + input/60.0;
                        input = 0; flag = 0; index = 10;
                    }
			    }
				break;

			case 4:
                if (lon_size == 3){
                    deg = input;
                    input = 0;
                }
                lon_size++;

                if (d == ',')
                    break;
                if (d == '.') {
                    flag = 1;
                    break;
                }
                if (!flag) input = input*10 + (int)d - 48;
                else {
                    input = input + ((int)d - 48)/ (index);
                    index *= 10;
                }

                break;

			case 5:
			    if (!got_lon){
                    got_lon= 1;
                    index = 0;
                    if (lon_size > 1){
                        current_pose -> lon_exists = 1;
                        current_pose -> longitude = deg + input / 60.0;
                        input = 0;
                    }
                }
				break;
        }
        if (d == ',') comma_counter++;
        d = UART1_read();
    }
}

void ftoa (double number, char* array){
  number *= 10000;
	int index0 = 0, index1 = 0, int_cast = (int) number;
	char temp[10];


	while (int_cast){
		temp[index0++] = 48 + (char)(int_cast % 10);
		int_cast /= 10;
	}

	int floating_pt_index = index0 - 4;

	for (index0 -= 1; index0 >= 0; index0--){
        if (index1 == floating_pt_index) {array[index1++] = '.'; index0++; continue;}
        array[index1++] = temp[index0];
	}
	if (index1 <= 10)
		array[index1] = '\0';
	else
		array[10] = '\0';
}
