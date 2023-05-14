#include "gps.h"

void filter_data(position* current_pose) {
	int lat_size = 0, lon_size = 0, comma_counter = 0;
	char found_lat = 0, found_lon = 0, found_point = 0;
	double accumulated_double = 0, degrees;
    
	char input_char = UART1_read();
	
	while (input_char != '$')
		input_char = UART1_read();

	double power_of_ten = 10;
	while (input_char != '*') {
		switch (comma_counter){
			case 2:
                if (lat_size == 2){
                    degrees = accumulated_double;
                    accumulated_double = 0;
                }
                lat_size++;

                if (input_char == ',')
                    break;
                if (input_char == '.') {
                    found_point = 1;
                    break;
                }
                if (!found_point) accumulated_double = accumulated_double * 10 + (int)input_char - 48;
                else {
                    accumulated_double = accumulated_double + (((int)input_char - 48) / power_of_ten);
                    power_of_ten *= 10;
                }

                break;
			case 3:
			    if (!found_lat){
                    found_lat = 1;
                    power_of_ten = 0;
                    if (lat_size > 1){
                        current_pose -> lat_exists = 1;
                        current_pose -> latitude = degrees + accumulated_double/60.0;
                        accumulated_double = 0; found_point = 0; power_of_ten = 10;
                    }
			    }
				break;

			case 4:
                if (lon_size == 3){
                    degrees = accumulated_double;
                    accumulated_double = 0;
                }
                lon_size++;

                if (input_char == ',')
                    break;
                if (input_char == '.') {
                    found_point = 1;
                    break;
                }
                if (!found_point) accumulated_double = accumulated_double*10 + (int)input_char - 48;
                else {
                    accumulated_double = accumulated_double + ((int)input_char - 48)/ (power_of_ten);
                    power_of_ten *= 10;
                }

                break;

			case 5:
			    if (!found_lon){
                    found_lon= 1;
                    power_of_ten = 0;
                    if (lon_size > 1){
                        current_pose -> lon_exists = 1;
                        current_pose -> longitude = degrees + accumulated_double / 60.0;
                        accumulated_double = 0;
                    }
                }
				break;
        }
        if (input_char == ',') comma_counter++;
        input_char = UART1_read();
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
