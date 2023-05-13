#include "gps.h"
#include "TM4C123.h"
#include "tm4c123gh6pm.h"
#include "UART.H"
int filter_data(char* unfiltered_data) {
	int i = 0;
	char d = UART1_read();
	
	while (d != '$') 
		d = UART1_read();
	if(d == '$')
	{
		while (d != '*') {
			unfiltered_data[i++] = d;
			d = UART1_read();
		}
		unfiltered_data[i++] = '\0';
	}
		
	
	if (i >= 5 && unfiltered_data[1] == 'G' && unfiltered_data[2] == 'P' && unfiltered_data[3] == 'G' && unfiltered_data[4] == 'G' && unfiltered_data[5] == 'A')
			return i + 1;
	else
			return -1;
}
void ftoa (double number, char* array){
  number *= 1000;
	int index0 = 0, index1 = 0, int_cast = (int) number;
	char temp[10];


	while (int_cast){
		temp[index0++] = 48 + (char)(int_cast % 10);
		int_cast /= 10;
	}

	int floating_pt_index = index0 - 3;

	for (index0 -= 1; index0 >= 0; index0--){
        if (index1 == floating_pt_index) {array[index1++] = '.'; index0++; continue;}
        array[index1++] = temp[index0];
	}
	if (index1 <= 10)
		array[index1] = '\0';
	else
		array[10] = '\0';
}
position get_pose_from_filtered_data(char* gps_data, int size) {
	char longitude[15], latitude[15];
	int lat_start = 0, lat_end = -1, lon_start = 0, lon_end = -1, comma_counter = 0, index = 0, i;

	position current_pose = {.lon_exists = 0, .lat_exists = 0};

	if (size <= 0) return current_pose;
	for (i = 0; i < size; i++) {
		if (gps_data[i] != ',') continue;

		comma_counter++;
		switch (comma_counter) {
				case 2:
					lat_start = i + 1;
					break;

				case 3:
					lat_end = i - 1;
					break;

				case 4:
					lon_start = i + 1;
					break;

				case 5:
					lon_end = i - 1;
					break;
			}

	}

	if (lat_end - lat_start <= 1 || lon_end - lon_start <= 1) return current_pose;
	for (i = lat_start; i <= lat_end; i++) {
			latitude[index++] = (char) (gps_data[i]);
			current_pose.lat_exists = 1;
	}
	latitude[index++] = '\0';

  get_latitude_from_array(&current_pose, latitude, index);

	index = 0;
	for (i = lon_start; i <= lon_end; i++) {
			longitude[index++] = (char) (gps_data[i]);
			current_pose.lon_exists = 1;
	}
	longitude[index++] = '\0';

  get_longitude_from_array(&current_pose, longitude, index);

  return current_pose;
}
void get_latitude_from_array(position* current_pose, char* latitude, int size){
  int i;
  char latitude_degrees_array[4];
	char latitude_minutes_array[12];

	for (i = 0; i < 2; i++){
		latitude_degrees_array[i] = latitude[i];
	}
	latitude_degrees_array[2] = '\0';

	for (i = 2; i < size; i++){
		latitude_minutes_array[i - 2] = latitude[i];
	}
	latitude_minutes_array[size] = '\0';
	current_pose->latitude = strtol(latitude_degrees_array, '\0', 10) + strtof(latitude_minutes_array, '\0') / 60.0;
}
void get_longitude_from_array(position* current_pose, char* longitude, int size){
	int i;
	char longitude_degrees_array[5];
	char longitude_minutes_array[15];

	for (i = 0; i < 3; i++){
		longitude_degrees_array[i] = longitude[i];
	}
	longitude_degrees_array[3] = '\0';

	for (i = 3; i < size; i++){
		longitude_minutes_array[i - 3] = longitude[i];
	}
	longitude_minutes_array[size] = '\0';
	current_pose->longitude = strtol(longitude_degrees_array, '\0', 10) + strtof(longitude_minutes_array, '\0') / 60.0;
}

