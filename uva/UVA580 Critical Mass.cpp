#include <cstdio>

/*
 * 没想到我也有自己想出了 dp 的一天，都准备放弃的时候突然灵机
 * 一动想出了 dp 的方案。
 *
 * 考虑当前规模为 n，则无非第一个位置放 L 或者放 U 两种情况。
 * 设 dp[n] 表示规模为 n 时危险的方案数，prefix[n][ix] 表示
 * 规模为 n 且不危险的方案中，前缀 U 的数量为 ix(ix = 0, 1, 2)
 * 的方案数。则有
 *
 * dp[n] = dp[n-1] + (dp[n-1] + prefix[n-1][2])
 *
 * 其中第一项表示首位置放 L，第二项表示首位置放 U。除此以外，还
 * 需要为 prefix 写状态转移函数，不难看出(
 *
 * prefix[n][2] = prefix[n-1][1]
 * prefix[n][1] = prefix[n-1][0]
 * prefix[n][0] = prefix[n-1][2] + prefix[n-1][1] + prefix[n-1][1]
 *
 * 前两个式子首位置放 U，最后一个式子首位置放 L。
 *
 * 然后看了 lrj 大神的题解，比我强不要太多......dp[n] 仍然沿用。
 * 枚举三个连续的 U 首次出现的位置，记为 i，此时 i-1 一定要是
 * L，则前 i-2 个位置的组合为不危险的方案数，即 2^(i-2) - dp[i-2]，
 * i + 2 之后任意组合，将所有 i 累加起来即可。
 */

int dp[31], prefix[31][3];

void init(){
	dp[1] = 0;
	prefix[1][0] = prefix[1][1] = 1;
	prefix[1][2] = 0;

	for(int ix = 2; ix <= 30; ++ix){
		dp[ix] = dp[ix-1] * 2 + prefix[ix-1][2];
		prefix[ix][2] = prefix[ix-1][1];
		prefix[ix][1] = prefix[ix-1][0];
		prefix[ix][0] = prefix[ix-1][0] + prefix[ix-1][1] + prefix[ix-1][2];
	}
}

int main(){
	init();
	int n;
	while(scanf("%d", &n) == 1){
		if(n == 0) break;
		printf("%d\n", dp[n]);
	}
	return 0;
}
