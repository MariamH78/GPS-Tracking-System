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