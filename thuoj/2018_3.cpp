#include <cstdio>
#define MOD  (991127)

int func(int one, int two){
	int curr = one & two, cnt = 0;
	while(curr){
		if(curr & 1) cnt++;
		curr = curr >> 1;
	}
	return cnt;
}

int main(){
	int n;
	scanf("%d", &n);
	int *arr = new int[n], *num_path = new int[n];
	for(int ix = 0; ix != n; ++ix)
		scanf("%d", arr + ix);
	num_path[n-1] = 1;
	for(int ix = n - 2; ix >= 0; --ix){
		for(int jx = ix + 1; jx != n; ++jx){
			num_path[ix] += (num_path[jx] * func(arr[ix], arr[jx])) % MOD;
			if(num_path[ix] > MOD) num_path[ix] = num_path[ix] % MOD;
		}
	}
	printf("%d\n", num_path[0]);
	return 0;
}
