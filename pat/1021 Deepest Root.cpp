#include <cstdio>
#include <vector>
using namespace std;

vector<vector<int>> tree;
vector<bool> visited;

int dfs(int root){
	visited[root] = true;
	if(tree[root].empty())
		return 0;
	int maxDepth = -1, curr;
	for(int e : tree[root])
		if(!visited[e]){
			curr = dfs(e);
			if(curr > maxDepth)
				maxDepth = curr;
		}
	return maxDepth + 1;
}


int main(){
	int N, one, two;
	scanf("%d", &N);
	tree = vector<vector<int>>(N + 1);
	visited = vector<bool>(N + 1, false);
	for(int ix = 1; ix != N; ++ix){
		scanf("%d %d", &one, &two);
		tree[one].push_back(two);
		tree[two].push_back(one);
	}

	int maxDepth, curr, K = 1;
	maxDepth = dfs(1);
	for(int ix = 1; ix <= N; ++ix)
		if(visited[ix] == false){
			++K;
			dfs(ix);
		}
	if(K != 1){
		printf("Error: %d components\n", K);
		return 0;
	}

	vector<int> res;
	res.push_back(1);
	for(int ix = 2; ix <= N; ++ix){
		for(auto it = visited.begin(); it != visited.end(); ++it)
			*it = false;
		curr = dfs(ix);
		if(curr > maxDepth){
			res.clear();
			res.push_back(ix);
			maxDepth = curr;
		}
		else if(curr == maxDepth)
			res.push_back(ix);
	}
	for(int e : res)
		printf("%d\n", e);
	return 0;
}
