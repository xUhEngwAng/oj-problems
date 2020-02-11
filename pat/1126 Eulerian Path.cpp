#include <cstdio>
#include <vector>
using namespace std;

/*
 * 这个题还是有一些意思的。我一开始的做法根本就没有保存图中
 * 的 edge 信息，而是直接管理一个 degree 向量，每读到一个
 * 顶点 vertex 就使 degree[vertex]++，最后判断 degree
 * 数组中为奇数的元素个数即可。
 * 
 * 然而这种方法会有一个测试点通不过。
 * 
 * 然后我又重新理解了一下题意，发现给出的图未必是连通的！而
 * 欧拉环路存在的必要条件显然是图得是连通的啊，所以修改了代
 * 码保存 edge 信息，然后做一次 dfs 判断连通性，这样就通过了。
 */

vector<vector<int>> graph;
vector<bool> visited;

void dfs(int origin){
    visited[origin] = true;
    for(int neighbor : graph[origin])
        if(!visited[neighbor])
            dfs(neighbor);
}

int main(){
	int N, M;
	scanf("%d %d", &N, &M);
	graph = vector<vector<int>>(N + 1);
	visited = vector<bool>(N + 1, false);

	int one, two;
	for(int ix = 0; ix != M; ++ix){
		scanf("%d %d", &one, &two);
		graph[one].push_back(two);
        graph[two].push_back(one);
	}

    dfs(1);
    bool connected = true;
    for(int ix = 1; ix <= N; ++ix)
        if(!visited[ix]){
            connected = false;
            break;
        }

	int oddcnt = 0;
	for(int ix = 1; ix <= N; ++ix)
		if(graph[ix].size() & 1) oddcnt++;

	printf("%d", graph[1].size());
	for(int ix = 2; ix <= N; ++ix)
		printf(" %d", graph[ix].size());
	if(oddcnt == 0 && connected)
		printf("\nEulerian\n");
	else if(oddcnt == 2 && connected)
		printf("\nSemi-Eulerian\n");
	else
		printf("\nNon-Eulerian\n");
	return 0;
}
