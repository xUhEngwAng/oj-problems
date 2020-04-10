#include <cstdio>
#include <cstdlib>

/*
 * 我好菜啊......这么水的题调试了半天，结果是爆 int 了......
 * 仔细算了算，如果不存在马，路径数最多是 40!/(20!20!)，所以
 * 爆 int 了，改成 long long 就通过了。
 */

long long dp[21][21];
int x, y;

bool isReachable(int row, int col){
	if(row == x && col == y) return false;
	int diff1 = abs(x - row);
	int diff2 = abs(y - col);
	if(diff1 == 2 && diff2 == 1) return false;
	if(diff1 == 1 && diff2 == 2) return false;
	return true;
}

int main(){
	int m, n;
	scanf("%d %d %d %d", &m, &n, &x, &y);
	for(int ix = 0; ix <= m; ++ix){
		for(int jx = 0; jx <= n; ++jx){
			if(!isReachable(ix, jx)) dp[ix][jx] = 0;
			else
			if(ix == 0 && jx == 0) dp[ix][jx] = 1;
			else if(ix == 0) dp[ix][jx] = dp[ix][jx-1];
			else if(jx == 0) dp[ix][jx] = dp[ix-1][jx];
			else dp[ix][jx] = dp[ix-1][jx] + dp[ix][jx-1];
			//printf("%d ", dp[ix][jx]);
		}
		//printf("\n");
	}
	printf("%lld\n", dp[m][n]);
	return 0;
}
