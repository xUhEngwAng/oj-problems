#include <stdio.h>
#include <stdlib.h>

#define MOVEUPTIME   6
#define MOVEDOWNTIME 4
#define STAYTIME     5

int main(){
	int N, currfloor, lastFloor = 0, upstage = 0, downstage = 0;
	scanf("%d", &N);

	for(int ix = 0; ix < N; ix++){
		scanf("%d",&currfloor);
		if(currfloor > lastFloor)
			upstage += currfloor - lastFloor;
		else
		if(currfloor < lastFloor)
			downstage += lastFloor - currfloor;

		lastFloor = currfloor;
	}

	int totalTime;
	totalTime = N*STAYTIME + upstage * MOVEUPTIME + downstage * MOVEDOWNTIME;
	printf("%d", totalTime);

	return 0;
}
