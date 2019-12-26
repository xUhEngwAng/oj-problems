#include <vector>
#include <stdio.h>

using std::vector;

int main(){
	int K;
	scanf("%d", &K);

	vector<int> intVec(K);
	for(vector<int>::size_type ix = 0; ix != K; ix++)
		scanf("%d", &intVec[ix]);
	vector<int>::const_iterator globalIter, localIter, begin, end;
	int maxSum = -1, currSum;
	for(globalIter = intVec.begin(); globalIter != intVec.end(); globalIter++){
		currSum = 0;
		for(localIter = globalIter; localIter != intVec.end(); localIter++){
			currSum += *localIter;
			if(currSum < 0) break;
			//else
			if(currSum > maxSum){
				maxSum = currSum;
				begin  = globalIter;
				end    = localIter;
			}
		}
	}
	if(maxSum == -1) printf("0 %d %d", intVec[0], intVec[K-1]);
	else             printf("%d %d %d", maxSum, *begin, *end);

	return 0;
}