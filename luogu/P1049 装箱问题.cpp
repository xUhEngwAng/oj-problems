#include <cstdio>

/*
 * 
 */

int volume[30];
int dp[20001][30];

int main(){
	int V, N, curr;
	scanf("%d %d", &V, &N);
	for(int ix = 0; ix != N; ++ix)
		scanf("%d", volume + ix);
	for(int ix = 0; ix <= V; ++ix){
		dp[ix][0] = ix - volume[0];
		if(dp[ix][0] < 0) dp[ix][0] = ix;
		for(int jx = 1; jx != N; ++jx){
			dp[ix][jx] = dp[ix][jx-1];
			if(ix >= volume[jx] && 
			   dp[ix-volume[jx]][jx-1] < dp[ix][jx])
				dp[ix][jx] = dp[ix-volume[jx]][jx-1];
		}
	}
	printf("%d\n", dp[V][N-1]);
	return 0;
}
