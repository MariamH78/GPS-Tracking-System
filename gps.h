#include "TM4C1234.h"
#include "UART.h"
#include <stdlib.h>
#define TARGET_LAT 30
#define TARGET_LON 30
int filter_data(char* data);
void ftoa(double number, char* array);

struct position{
	double longitude;
	double latitude;
  char lon_exists;
	char lat_exists;
};
typedef struct position position;
