#include <stdio.h>
#include <stdlib.h>

#define RATIO 0.65

int main(){
	float currWin, currTie, currLose;
	char bestBet[4];
	float profit = 1;

	for(short int ix = 0; ix < 3; ix++){
		scanf("%f %f %f",&currWin, &currTie, &currLose);
		if(currWin > currTie){
			if(currWin > currLose) bestBet[ix] = 'W',profit*=currWin;
			else                   bestBet[ix] = 'L',profit*=currLose;
		}else{
			if(currTie > currLose) bestBet[ix] = 'T',profit*=currTie;
			else                   bestBet[ix] = 'L',profit*=currLose;
		}
	}

	profit = (profit*RATIO-1)*2;
	printf("%c %c %c %.2f", bestBet[0],bestBet[1],bestBet[2],profit);
	return 0;
}
