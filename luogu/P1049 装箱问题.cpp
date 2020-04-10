#include <cstdio>

/*
 * 这个题本身是简单的，我是利用了类似于0-1背包问题的状态以及
 * 状态转移来做的，别的到没有多想什么。看了大佬的题解，才想到
 * 原来这个题的本质就是0-1背包问题啊，只不过每个物体的权重恰
 * 好等于其体积，要求在有限的体积内，物体的权重之和为最大（即
 * 剩余的容量最小）。
 *
 * 然后我的dp数组也是用了二维的，实际上用一维的就可以了。
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
