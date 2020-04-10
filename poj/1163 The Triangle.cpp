#include <cstdio>
#include <cstring>

int maxSum[102], curr[102];

int main(){
	int n, res;
	scanf("%d", &n);
	memset(maxSum, 0, sizeof(maxSum));
	for(int ix = 1; ix <= n; ++ix){
		for(int jx = 1; jx <= ix; ++jx)
			scanf("%d", curr + jx);
        for(int jx = ix; jx >= 1; --jx){
            if(maxSum[jx - 1] > maxSum[jx])
                maxSum[jx] = maxSum[jx - 1];
			maxSum[jx] += curr[jx];
        }
	}
	res = 0;
	for(int ix = 1; ix <= n; ++ix)
		if(maxSum[ix] > res) res = maxSum[ix];
	printf("%d\n", res);
	return 0;
}
