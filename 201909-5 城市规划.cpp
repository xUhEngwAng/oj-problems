#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

#define INF (1LL << 50)

struct node{
	int id;
	int weight;
	node() = default;
	node(int i, int w): id(i), weight(w){}
};

vector<vector<node>> tree;
long long dp[50001][101];
bool impt[50001];
int n, m, k;

void dfs(int origin){
	dp[origin][0] = 0;
	if(impt[origin]) dp[origin][1] = 0;
	long long temp;
	for(auto entry : tree[origin]){
		if(dp[entry.id][0] != 0){
			dfs(entry.id);
			for(int ix = k; ix >= 1; --ix)
				for(int jx = 1; jx <= ix; ++jx){
					temp = dp[origin][ix - jx] + dp[entry.id][jx] + entry.weight * jx * (k - jx);
					if(temp < dp[origin][ix])
						dp[origin][ix] = temp;
				}
		}
	}
	/*
	printf("%d: ", origin);
	for(int ix = 1; ix <= k; ++ix)
        if(dp[origin][ix] == INF) printf("INF ");
        else printf("%d ", dp[origin][ix]);
    printf("\n");*/
}

int main(){
	int curr, next, weight;
	scanf("%d %d %d", &n, &m, &k);
	tree.resize(n + 1);
	memset(impt, 0, sizeof(bool) * (n + 1));
	for(int ix = 1; ix <= n; ++ix)
        for(int jx = 0; jx <= k; ++jx)
            dp[ix][jx] = INF;
	for(int ix = 0; ix != m; ++ix){
		scanf("%d", &curr);
		impt[curr] = 1;
	}
	for(int ix = 0; ix != n - 1; ++ix){
		scanf("%d %d %d", &curr, &next, &weight);
		tree[curr].emplace_back(next, weight);
		tree[next].emplace_back(curr, weight);
	}
	dfs(1);
	printf("%d\n", dp[1][k]);
	return 0;
}
