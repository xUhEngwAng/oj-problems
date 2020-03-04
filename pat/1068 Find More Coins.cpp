#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * 好好学习了0-1背包问题后，终于把这个题给解决了。一开始
 * 我用的是 dfs 的方案，无奈 N 最多可以有 10,000 个，
 * dfs 这种低效方案不可避免地超时了。
 *
 * 然后改用 0-1 背包问题的方案。这里用 dp[i][j] 来表示
 * 要付的价格为 j 时，用前 i 个硬币实际上最多可以付出的
 * 不大于 j 价格，这就相当于背包问题中的物体质量和体积
 * 都是相同的，且都是这里硬币的面额。最后，只需判断 dp[N][M]
 * 是否等于 M，即可判断是否存在一组可行的解。
 *
 * 此外还有一个问题，需要打印最小的一组解。为了获得最小解，
 * 我首先对数据进行了降序排序，这样最后的数据对应了最小的
 * 硬币面额。此后，就是对 dp[N][M] 进行回溯，即判断 dp[N][M]
 * 究竟是从 dp[N - 1][M] 还是 dp[N - 1][M - coins[N - 1]]
 * 更新得到的，如果可以同时从两者更新，则选择后者，因为当前
 * 的硬币是最小面额的硬币了。
 */

vector<int> seq;
int *coins, M, N;

int dfs(int origin, int sum){
	sum += coins[origin];
	seq.push_back(coins[origin]);
	if(sum > M){
		seq.pop_back();
		return -1;
	}
	if(sum == M) return 1;

	int ret;
	for(int ix = origin + 1; ix <= N; ++ix){
		ret = dfs(ix, sum);
		if(ret == -1) break;
		if(ret == 1) return ret;
	}
	seq.pop_back();
	return 0;
}

int _main(){
	scanf("%d %d", &N, &M);
	coins = new int[N + 1];
	coins[0] = 0;
	for(int ix = 1; ix <= N; ++ix)
		scanf("%d", coins + ix);
	sort(coins, coins + N + 1);
	int ret = dfs(0, 0);
	if(ret == 1){
		printf("%d", seq[1]);
		for(int ix = 2; ix != seq.size(); ++ix)
			printf(" %d", seq[ix]);
		printf("\n");
	}
	else
        printf("No Solution\n");
	return 0;
}

bool cmp(int one, int two){return one > two;}

int main(){
	int N, M;
	scanf("%d %d", &N, &M);
	vector<vector<int>> dp(N + 1, vector<int>(M + 1));
	int *coins = new int[N + 1];
	for(int ix = 0; ix != N; ++ix)
		scanf("%d", coins + ix);
	sort(coins, coins + N, cmp);
	for(int ix = 0; ix != N; ++ix){
		for(int jx = 1; jx <= M; ++jx){
			dp[ix + 1][jx] = dp[ix][jx];
			if(jx >= coins[ix] &&
			   dp[ix][jx - coins[ix]] + coins[ix] > dp[ix][jx])
				dp[ix + 1][jx] = dp[ix][jx - coins[ix]] + coins[ix];
		}
	}
	if(dp[N][M] != M){
		printf("No Solution\n");
		return 0;
	}
	vector<int> seq;
	int row = N, col = M, curr;
	while(col > 0 && row > 0){
		curr = coins[row - 1];
		if(col >= curr &&
		   dp[row - 1][col - curr] + curr >= dp[row - 1][col]){
			col -= curr;
			seq.push_back(curr);
		}
		--row;
	}
	printf("%d", seq.front());
	for(int ix = 1; ix != seq.size(); ++ix)
		printf(" %d", seq[ix]);
	printf("\n");
	return 0;
}
