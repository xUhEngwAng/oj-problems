#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define NUMOFMONTH 12

int main(){
	float aver = 0;
	float balance;
	for(int ix = 0; ix != NUMOFMONTH; ++ix){
		scanf("%f", &balance);
		aver += balance;
	}
	aver = aver / NUMOFMONTH;

	//round to the nearest penny
	int digits = (int)aver, first, second;
	float decimals = aver - digits;
	first = (int)(decimals * 10);
	decimals -= 0.1 * first;
	second = (int)(decimals * 100);
	decimals -= 0.01 * second;
	if (decimals > 0.005) second++;
	float res = digits + 0.1 * first + 0.01 * second;
	printf("$%.2f", res);

	while (getchar() != ' ');
	return 0;
}
