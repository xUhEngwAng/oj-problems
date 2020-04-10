#include <cstdio>

int arr[20];

int main(){
	int N, cnt = 0;
	long long curr, max;
	while(scanf("%d", &N) == 1){
		for(int ix = 0; ix != N; ++ix)
			scanf("%d", arr + ix);
		max  = 0;
		for(int ix = 0; ix != N; ++ix){
			curr = 1;
			for(int jx = ix; jx != N; ++jx){
				curr = curr * arr[jx];
				if(curr > max) max = curr;
			}
		}
		printf("Case #%d: The maximum product is %lld.\n\n", ++cnt, max);
	}
	return 0;
}
