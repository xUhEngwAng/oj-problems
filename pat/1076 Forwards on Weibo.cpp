#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

/*
 * 此题我一看这么简单，不就一个有向图，对每一个 query 都做
 * 一个以其为 root 的 dfs 就结束了吗？结果死活通不过两个
 * 点。
 *
 * 实际上，这个题不适合用 dfs 来做，考虑一种情况，在某次访
 * 问中，当前节点的深度为 L，因此不能再往下深入进行了，直接
 * 返回即可。但是该节点已经被标记为 visited；考虑通过另一条
 * 路径，可以在深度 L 之前就访问到该节点，从而该节点的后续
 * 节点也因此可以得到访问，但是由于它已经被标记为 visited，
 * 后续的访问中都会忽略到节点，从而出错。
 *
 * 所以，这个题最好的方案是用 bfs 来做，就可以规避上面的问题。 
 */

vector<vector<int>> graph;
vector<bool> visited;
int N, L;

int bfs(int root){
    int curr, count = 1, level = 0, res = 0, nextCount = 0;
    queue<int> q;
    q.push(root);
    visited[root] = true;
    while(!q.empty()){
        curr = q.front();
        q.pop();
        ++res;
        for(auto e : graph[curr])
            if(!visited[e]){
                q.push(e);
                visited[e] = true;
                ++nextCount;
            }
        if(--count == 0){
            count = nextCount;
            nextCount = 0;
            ++level;
            if(level == L + 1)
                break;
        }
    }
    return res - 1;
}

int dfs(int root, int depth){
	int res = 0;
	visited[root] = true;
	if(graph[root].empty() || depth == L)
		return res;
	for(auto e : graph[root])
		if(!visited[e]){
			res += dfs(e, depth + 1) + 1;
		}
	return res;
}

int main(){
	int count, curr;
	scanf("%d %d", &N, &L);
	graph = vector<vector<int>>(N + 1);
	visited = vector<bool>(N + 1, false);
	for(int ix= 1; ix <= N; ++ix){
		scanf("%d", &count);
		while(count--){
			scanf("%d", &curr);
			graph[curr].push_back(ix);
		}
	}

	int K, query, amount;
	scanf("%d", &K);
	while(K--){
		scanf("%d", &query);
		amount = bfs(query);
		printf("%d\n", amount);
		for(int ix = 1; ix <= N; ++ix)
			visited[ix] = false;
	}
	return 0;
}
