#include <stdio.h>
#include <vector>

using std::vector;

#define ERROR 65535

struct colors{
	int value; //24bits of information
	int count; //repeating times
};

inline vector<colors>::size_type findIx(vector<colors> color, int colorValue);


int main(int argc, char* argv[]){
	short M,N;
	scanf("%hd", &M);
	scanf("%hd", &N);
	int dominantSize = M*N/2;

	int currBit;
	colors currColor;
	vector<colors> color;
	vector<colors>::size_type pos;

	for(short ix = 0; ix < N; ix++){
		for(short jx = 0; jx < M; jx++){
			scanf("%d", &currBit);
			pos = findIx(color, currBit);
			if(pos == ERROR){//do not exist current color value
				currColor.value = currBit;
				currColor.count = 1;
				color.push_back(currColor);
			}else{//already exist a same value
				color[pos].count++;
			}
		}
	}

	vector<colors>::const_iterator iter;
	for(iter = color.begin(); iter != color.end(); iter++){
		if(iter->count > dominantSize){
			printf("%d\n", iter->value);
		}
	}
	return 0;	
}

inline vector<colors>::size_type findIx(vector<colors> color, int colorValue){
	vector<colors>::size_type pos;
	for(pos = 0; pos != color.size(); pos++){
		if(color[pos].value == colorValue){
			return pos;
		}
	}

	return ERROR;
}
