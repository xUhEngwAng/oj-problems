#include <cstdio>

/*
 * 这个题的思路非常简单，稍作思考就可以想出一个 O(n) 的算法。
 * 我这里遇到的问题是出现了『格式错误』。后来才发现，即使结果为
 * 零，第二行也需要输出一个空行。改正了就 AC 了。
 */

int main(){
	int N;
	scanf("%d", &N);
	int *arr = new int[N];
	int *max = new int[N], *min = new int[N];
	for(int ix = 0; ix != N; ++ix)
		scanf("%d", arr + ix);
	max[0] = arr[0];
	for(int ix = 1; ix != N; ++ix)
		if(arr[ix] > max[ix - 1])
			max[ix] = arr[ix];
		else
			max[ix] = max[ix - 1];
	min[N - 1] = arr[N - 1];
	for(int ix = N - 2; ix >= 0; --ix)
		if(arr[ix] < min[ix + 1])
			min[ix] = arr[ix];
		else
			min[ix] = min[ix + 1];
	int count = 0;
	int *res = new int[N];
	for(int ix = 0; ix != N; ++ix){
		if(arr[ix] == max[ix] && arr[ix] == min[ix])
			res[count++] = arr[ix];
	}
	printf("%d\n", count);
	if(count != 0)
		printf("%d", res[0]);
	for(int ix = 1; ix < count; ++ix)
		printf(" %d", res[ix]);
    printf("\n");
	return 0;
}
