#include "TM4C1234.h"
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

void get_latitude_from_array(position* current_pose, char* latitude, int size);
void get_longitude_from_array(position* current_pose, char* longitude, int size);
position  get_pose_from_filtered_data(char* gps_data, int size);