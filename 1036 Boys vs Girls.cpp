#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 11

int main(){
	int N;
	scanf("%d", &N);

	char currName[LEN], currId[LEN], currGender;
	char highName[LEN], lowName[LEN], highId[LEN], lowId[LEN];
	short int currGrade, highGrade = -1, lowGrade = 101;

	//main loop
	for(int ix = 0; ix < N; ix++){
		scanf("%s %c %s %hd", currName, &currGender, currId, &currGrade);
		switch(currGender){
			case 'F':
			if(currGrade > highGrade){
				highGrade = currGrade;
				strcpy(highName,currName);
				strcpy(highId,currId);
			}
			break;

			case 'M':
			if(currGrade < lowGrade){
				lowGrade = currGrade;
				strcpy(lowName, currName);
				strcpy(lowId, currId);
			}
			break;
		}
	}

	//output result
	if(highGrade == -1) printf("Absent\n");
	else printf("%s %s\n", highName, highId);

	if(lowGrade == 101) printf("Absent\n");
	else printf("%s %s\n", lowName, lowId);

	if(highGrade == -1 || lowGrade == 101) printf("NA\n");
	else{
		short int difference = highGrade - lowGrade;
		printf("%hd", difference);
	}
	

	return 0;
}
