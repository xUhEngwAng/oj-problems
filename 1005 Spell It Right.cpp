#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 101

const char* digits[10] = {"zero", "one", "two", "three", "four",
                          "five", "six", "seven", "eight","nine"};

int main(){
	char N[MAXLEN];
	scanf("%s", N);

	int sum = 0, currNum,tmp;
	for(short int ix = 0; N[ix] != '\0'; ix++){
		currNum = N[ix] - '0';
		sum += currNum;
	}
	int base = 1;
	tmp = sum;
	while(tmp/10 != 0){
		tmp = tmp/10;
		base *= 10;
	}
	short int thisbit;
	thisbit = sum/base;
	sum = sum % base;
	base /= 10;
	printf("%s", digits[thisbit]);
	while(base != 0){
		thisbit = sum/base;
		sum = sum % base;
		base /= 10;
		printf(" %s", digits[thisbit]);
	}

	return 0;
}
