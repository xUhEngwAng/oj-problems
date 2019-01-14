#include <stdio.h>
#include <stdlib.h>

#define RADIX 13
#define NUM    3

const char convert[14] = "0123456789ABC";

int main(){
	short int color[NUM];//decimal numbers
	scanf("%hd %hd %hd", &color[0], &color[1], &color[2]);

	//convert to radix 13
	printf("#");
	short int tens, units;
	for(short int ix = 0; ix < NUM; ix++){
		tens  = color[ix] / RADIX;
		units = color[ix] - tens*RADIX;	
		printf("%c%c", convert[tens],convert[units]);
	}
	

	return 0;
}
