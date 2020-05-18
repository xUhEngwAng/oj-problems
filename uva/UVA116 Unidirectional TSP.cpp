#include <cstdio>
#include <cstring>
#include <vector>
using std::vector;

struct entry{
	long long weight;
	int prev;
}dp[11][101];

int matrix[11][101];
vector<int> seq;

int main(){
	freopen("1.out", "w", stdout);
	int m, n, pos;
	while(scanf("%d %d", &m, &n) == 2){
		for(int ix = 1; ix <= m; ++ix)
		for(int jx = 1; jx <= n; ++jx)
			scanf("%d", &matrix[ix][jx]);
		memset(dp, 0, sizeof(dp));
		for(int ix = 1; ix <= n; ++ix)
		for(int jx = 1; jx <= m; ++jx){
			dp[jx][ix].weight = dp[jx][ix-1].weight;
			dp[jx][ix].prev = jx;
			if((pos = jx - 1) == 0) pos = m;
			if(dp[pos][ix-1].weight < dp[jx][ix].weight){
				dp[jx][ix].weight = dp[pos][ix-1].weight;
				dp[jx][ix].prev = pos;
			}
			if(dp[pos][ix-1].weight == dp[jx][ix].weight)
				if(pos < dp[jx][ix].prev)
					dp[jx][ix].prev = pos;
			if((pos = jx + 1) == m + 1) pos = 1;
			if(dp[pos][ix-1].weight < dp[jx][ix].weight){
				dp[jx][ix].weight = dp[pos][ix-1].weight;
				dp[jx][ix].prev = pos;
			}
			if(dp[pos][ix-1].weight == dp[jx][ix].weight)
				if(pos < dp[jx][ix].prev)
					dp[jx][ix].prev = pos;
			dp[jx][ix].weight += matrix[jx][ix];
		}
		/*for(int ix = 1; ix <= m; ++ix){
			for(int jx = 1; jx <= n; ++jx)x
				printf("%d ", dp[ix][jx].weight);
			printf("\n");
		}*/
		pos = 1;
		for(int ix = 2; ix <= m; ++ix)
			if(dp[ix][n].weight < dp[pos][n].weight) pos = ix;
		seq.clear();
		for(int ix = n, jx = pos; ix > 0; --ix){
			seq.push_back(jx);
			jx = dp[jx][ix].prev;
		}
		printf("%d", seq.back());
		for(int ix = seq.size() - 2; ix >= 0; --ix)
			printf(" %d", seq[ix]);
		printf("\n%d\n", dp[pos][n].weight);
	}
	return 0;
}
