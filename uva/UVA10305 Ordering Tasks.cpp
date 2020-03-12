#include <cstdio>
#include <vector>
using namespace std;

vector<vector<int>> graph;
vector<bool> visited;
vector<int> res;

void dfs(int src){
	visited[src] = true;
	for(int e : graph[src])
		if(!visited[e])
			dfs(e);
	res.push_back(src);
}

int main(){
	int m, n, one, two;
	while(true){
		scanf("%d %d", &n, &m);
		if(n == 0) break;
		graph.clear();
		graph.resize(n + 1);
		for(int ix = 0; ix != m; ++ix){
			scanf("%d %d", &one, &two);
			graph[one].push_back(two);
		}
		res.clear();
		visited.clear();
		visited.resize(n + 1);
		for(int ix = 1; ix <= n; ++ix)
			if(!visited[ix])
				dfs(ix);
		printf("%d", res.back());
		for(int ix = res.size() - 2; ix >= 0; --ix)
			printf(" %d", res[ix]);
		printf("\n");
	}
	return 0;
}
