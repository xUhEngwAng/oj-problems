#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

struct edge{
	int node;
	int cost;
	edge() = default;
	edge(int n, int c): node(n), cost(c){}
};

int value[2001], dp[2001][801];
vector<vector<edge>> g(2001);

int dfs(int origin, int cost){
	if(dp[origin][cost] != -1) return dp[origin][cost];
	//if(cost == 0) return dp[origin][cost] = value[origin];

	int curr, max = 0;
	for(auto e : g[origin]){
		if(e.cost <= cost){
			curr = dfs(e.node, cost - e.cost);
			if(curr > max) max = curr;
		}
	}
	//printf("%d\n", max);
	max += value[origin];
	dp[origin][cost] = max;
	return max;
}

int main(){
	int n, m, q;
	int x, y, z, u, c;
	scanf("%d %d %d", &n, &m, &q);
	for(int ix = 1; ix <= n; ++ix)
		scanf("%d", value + ix);
	for(int ix = 0; ix != m; ++ix){
		scanf("%d %d %d", &x, &y, &z);
		g[x].emplace_back(y, z);
	}
	
	for(int ix = 1; ix <= n; ++ix)
	for(int jx = 0; jx <= 800; ++jx)
		dp[ix][jx] = -1;
	for(int ix = 0; ix != q; ++ix){
		scanf("%d %d", &u, &c);
		printf("%d\n", dfs(u, c));
	}
	return 0;
}
