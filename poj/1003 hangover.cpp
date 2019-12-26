#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAXNUM 276

int main(){
	//construct hangover[]
	double hangover[MAXNUM];
	double sum = 0.0;
	int ix = 1;
	hangover[0] = 0.5;
	while(hangover[ix - 1] <= 5.20){
		hangover[ix] = hangover[ix - 1] + 1.0 / (ix + 2);
		++ix;
	}

	double input;
	int lo, hi, mid;		
	while(true){
		lo = 0, hi = ix;					//[lo, hi)
		scanf("%lf", &input);
		if (input == 0.00) break;
		//binary search
		while(lo < hi){
			mid = (lo + hi) >> 1;
			if (hangover[mid] <= input) lo = mid + 1;
			else                        hi = mid;
		}
		printf("%d card(s)\n", lo + 1);
	}
	return 0;
}
