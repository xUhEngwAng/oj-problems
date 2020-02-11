#include <algorithm>
#include <cstdio>
using namespace std;

int main(){
	int N;
	scanf("%d", &N);
	int *arr = new int[N];
	for(int ix = 0; ix != N; ++ix)
		scanf("%d", arr + ix);
	sort(arr, arr + N);
	int bigsum = 0, smallsum = 0;
	for(int ix = 0; ix < (N >> 1); ++ix)
		smallsum += arr[ix];
	for(int ix = N >> 1; ix != N; ++ix)
		bigsum += arr[ix];
	if(N & 1) printf("1 %d\n", bigsum - smallsum);
	else printf("0 %d\n", bigsum - smallsum);
	return 0;
}
