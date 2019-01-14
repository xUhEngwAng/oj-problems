#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 14

struct testee{
	short int score;
	short int ranking;
	char regisNum[LEN];
};

//one ranklist
struct Testee{
	short int K; // the number of testees
	testee* testees; // info
};

void selectSort(testee array[], short int N);

int main(){
	short int N, entryNum = 0;//N ranklists
	scanf("%hd", &N);

	Testee allEntry[N];
	short int K;
	for(short int ix = 0; ix < N; ix++){
		//input data
		scanf("%hd", &K);//current number of testees
		entryNum += K;

		allEntry[ix].testees = (testee*)malloc(sizeof(testee)*K);
		allEntry[ix].K       = K;
		for(short int jx = 0; jx < K; jx ++)
			scanf("%s %hd", allEntry[ix].testees[jx].regisNum, 
				            &allEntry[ix].testees[jx].score);

		//select sort
		selectSort(allEntry[ix].testees, allEntry[ix].K);
	}

	printf("%hd\n", entryNum);

	//merge
	short int indexes[N] = {0}, currix, count = 1, ranking = 1;
	short int maxScore, maxPos, lastMax = -1, lastRanking = -1;
	char maxRegisNum[LEN];
	while(1){
		maxScore = -1;
		for(short int ix = 0; ix < N; ix++){
			currix = indexes[ix];
			if(currix == allEntry[ix].K) continue;//overflow

			//else
			if(allEntry[ix].testees[currix].score > maxScore){
				maxScore = allEntry[ix].testees[currix].score;
				maxPos   = ix;
				strcpy(maxRegisNum, allEntry[ix].testees[currix].regisNum);
			}else
			if(allEntry[ix].testees[currix].score == maxScore){
				if(strcmp(allEntry[ix].testees[currix].regisNum, 
					      maxRegisNum) < 0){
					maxPos   = ix;
					strcpy(maxRegisNum, allEntry[ix].testees[currix].regisNum);
				}
			}
			//else pass
		}
		if(maxScore == -1) break;//end merge

		//else

		//detect same ranking
		if(maxScore == lastMax) ranking = lastRanking;
		else{
			lastMax = maxScore;
			ranking = count;
			lastRanking = ranking;
		}

		printf("%s %hd %hd %hd\n", maxRegisNum, ranking,
			                     maxPos+1, allEntry[maxPos].testees[indexes[maxPos]].ranking);
		count++, indexes[maxPos]++;
		
	}

	return 0;
}

void selectSort(testee array[], short int N){
	if(array == NULL || N == 0) return;

	//else
	short int ix, jx;
	short int maxScore, maxPos, lastMax = -1, lastRanking = -1;
	testee tmp;
	for(ix = 0; ix < N; ix++){
		maxScore = array[ix].score;
		maxPos   = ix;
		for(jx = ix+1; jx < N; jx++){
			if(array[jx].score > maxScore){
				maxScore = array[jx].score;
				maxPos   = jx;
			}else
			if(array[jx].score == maxScore){
				if(strcmp(array[jx].regisNum, array[maxPos].regisNum) < 0){
					maxScore = array[jx].score;
					maxPos   = jx;
				}
			}
			//else
		}
		//update ranking
		if(maxScore == lastMax) array[maxPos].ranking = lastRanking;
		else{
			lastMax = maxScore;
			array[maxPos].ranking = ix + 1;
			lastRanking = array[maxPos].ranking;
		}

		//swap
		tmp = array[maxPos];
		array[maxPos] = array[ix];
		array[ix] = tmp;
	}
}
