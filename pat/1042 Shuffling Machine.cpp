#include <stdio.h>
#include <stdlib.h>

#define NUM 54

short int find(short int order[], short int N, short int dest);

int main(){
	short int K;//repeat times
	scanf("%hd", &K);

	short int order[NUM];
	for(short int ix = 0; ix < NUM; ix++){
		scanf("%hd", &order[ix]);
	}

	//main loop
	short int pos, type, offset;
	for(short int ix = 1; ix <= NUM; ix++){
		pos = ix;
		for(short int jx = 0; jx < K; jx++){
			pos = find(order, NUM, pos);
		}

		//print result
		type   = (pos-1)/13;
		offset = pos - 13*type;
		switch(type){
			case 0:
			printf("S");
			break;

			case 1:
			printf("H");
			break;

			case 2:
			printf("C");
			break;

			case 3:
			printf("D");
			break;

			case 4:
			printf("J");
			break;
		}
		printf("%hd", offset);
		if(ix != NUM) printf(" ");
	}
	return 0;
}

inline short int find(short int order[], short int N, short int dest){
	if(order == NULL || N == 0) return -1;

	//else
	for(short int ix = 0; ix < N; ix++){
		if(order[ix] == dest) return ix+1;
	}
}
