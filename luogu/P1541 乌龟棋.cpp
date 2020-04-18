#include <cstdio>
#include <cstring>
#define MAX(X, Y) ((X) > (Y)? (X): (Y))

/*
 * 这个题看了大佬的题解之后才会做，感觉还是比较巧妙的。
 *
 * 一开始也做了一些努力，比如试图以 dp[ix] 来表示到达第 ix 个
 * 格子所能获得的最大分数，这样最终答案就是 dp[N]。然而这样设计
 * 的状态不满足最优子结构，因为无法使用 dp[ix-1] 这种来更新
 * dp[ix]。这是因为盲目寻求局部最大分数会导致快速消耗卡片，从而
 * 在以后的决策中可能不得不错过某些分值高的格子。本质来讲，这种
 * 做法是采用贪心的策略。
 *
 * 然后看了看大佬的题解，是用 dp[a][b][c][d] 来表示各个类型的
 * 卡片的消耗量分别为 a, b, c, d 时所能获得的最大分数。这样可以
 * 轻易地构造出状态转移函数，以第一类卡片为例：
 *
 * dp[a][b][c][d] = MAX(dp[a][b][c][d], 
 * dp[a-1][b][c][d] + num[a + 2b + 3c + 4d])
 *
 * 这样就可以求解了。通过和 0-1 背包问题进行比较，可以发现该转移
 * 函数等价于多个约束（四种牌的数量）的 0-1 背包问题，每个物品
 * 占用的空间为 1，价值则为 num[a + 2b + 3c + 4d]。
 */

int num[350], cnt[5];
int dp[41][41][41][41];

int main(){
	int N, M, curr;
	scanf("%d %d", &N, &M);
	for(int ix = 0; ix != N; ++ix)
		scanf("%d", num + ix);
	memset(cnt, 0, sizeof(cnt));
	for(int ix = 0; ix != M; ++ix){
		scanf("%d", &curr);
		cnt[curr]++;
	}
	memset(dp, 0, sizeof(dp));
	dp[0][0][0][0] = num[0];
	curr = 0;
	for(int a = 0; a <= cnt[1]; ++a)
	for(int b = 0; b <= cnt[2]; ++b)
	for(int c = 0; c <= cnt[3]; ++c)
	for(int d = 0; d <= cnt[4]; ++d){
		curr = a + 2 * b + 3 * c + 4 * d;
		if(a != cnt[1]) dp[a+1][b][c][d] = MAX(dp[a+1][b][c][d], dp[a][b][c][d] + num[curr+1]);
		if(b != cnt[2]) dp[a][b+1][c][d] = MAX(dp[a][b+1][c][d], dp[a][b][c][d] + num[curr+2]);
		if(c != cnt[3]) dp[a][b][c+1][d] = MAX(dp[a][b][c+1][d], dp[a][b][c][d] + num[curr+3]);
		if(d != cnt[4]) dp[a][b][c][d+1] = MAX(dp[a][b][c][d+1], dp[a][b][c][d] + num[curr+4]);
	}
	printf("%d\n", dp[cnt[1]][cnt[2]][cnt[3]][cnt[4]]);
	return 0;
}
