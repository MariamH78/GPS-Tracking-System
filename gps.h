#ifndef GPS_HEADER
#define GPS_HEADER

#include "UART.h"

#define TARGET_LAT 30
#define TARGET_LON 30

void ftoa(double number, char* array);

struct position{
	double longitude;
	double latitude;
  char lon_exists;
	char lat_exists;
};
typedef struct position position;


void filter_data(position* current_pose);

#endif

