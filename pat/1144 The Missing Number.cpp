#include <cstdio>
#include <algorithm>
using namespace std;

int main(){
	int N, count = 0, curr;
	scanf("%d", &N);
	int *arr = new int[N];
	for(int ix = 0; ix != N; ++ix){
		scanf("%d", &curr);
		if(curr > 0)
			arr[count++] = curr;
	}
	sort(arr, arr + count);
	int pos = unique(arr, arr + count) - arr;
	for(int ix = 1; ix <= pos; ++ix)
		if(arr[ix - 1] != ix){
			printf("%d\n", ix);
			return 0;
		}
	printf("%d\n", pos + 1);
	return 0;
}
