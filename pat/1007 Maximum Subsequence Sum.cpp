#include <cstdio>

/*
 * 这个题是典型的动态规划题啊，我是用了两种方法来解决，都是
 * 最常见的那种方案，就不多说了。
 */

int main(){
	int K;
	scanf("%d", &K);
	int *arr = new int[K];
	for(int ix = 0; ix != K; ++ix)
		scanf("%d", arr + ix);
	int currSum, maxSum = -1, begin, end;
	for(int ix = 0, jx; ix < K; ){
		currSum = 0;
		for(jx = ix; jx < K; ++jx){
			currSum += arr[jx];
			if(currSum < 0) break;
			if(currSum > maxSum){
				maxSum = currSum;
				begin = ix, end = jx;
			}
		}
		ix = jx + 1;
	}
	if(maxSum == -1){
		printf("0 %d %d\n", arr[0], arr[K - 1]);
		return 0;
	}
	printf("%d %d %d\n", maxSum, arr[begin], arr[end]);
	return 0;
}

int main(){
	int K;
	scanf("%d", &K);
	int *arr = new int[K];
	int *currSum = new int[K], maxSum, endpos;
	for(int ix = 0;ix != K; ++ix)
		scanf("%d", arr + ix);
	currSum[0] = arr[0];
	maxSum = arr[0];
	endpos = 0;
	for(int ix = 1; ix != K; ++ix){
		if(currSum[ix - 1] < 0)
			currSum[ix] = arr[ix];
		else
			currSum[ix] = arr[ix] + currSum[ix - 1];
		if(currSum[ix] > maxSum){
			maxSum = currSum[ix];
			endpos = ix;
		}
	}
	if(maxSum < 0){
		printf("0 %d %d\n", arr[0], arr[K - 1]);
		return 0;
	}
	int sum = arr[endpos], startpos = endpos;
	while(sum != maxSum){
		sum += arr[--startpos];
	}
	printf("%d %d %d\n", maxSum, arr[startpos], arr[endpos]);
	return 0;
}
