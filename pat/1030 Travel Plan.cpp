#include <vector>
#include <cstdio>
using namespace std;

/*
 * 好久不写最短路径的题了，我都快忘了怎么写了。本来是想用
 * Dijkstra 写的，无奈确实忘了怎么保证路径最短且代价最小
 * 小了......结果用 dfs 写的，本质上是试探回溯法，也是
 * 得亏这个题的数据量比较小，dfs 也轻松通过了。
 *
 * 于是去好好复习了一下怎么用 Dijkstra 来写这个题，需要
 * 注意的点主要是，在有多条最优路径时，可以引入一个 num
 * 数组来保存路径数，引入一个两位数组（向量） prev 来保
 * 存所有节点的前驱节点。这样，可以通过后续做一次 dfs 来
 * 确定最优的那条路径。这里主要是看我柳神的总结：
 *
 * https://www.liuchuo.net/archives/tag/最短路径
 */

struct edge{
	int id;
	int dist;
	int cost;

	edge(int id, int d, int c): id(id), dist(d), cost(c){}
};

vector<vector<edge>> graph;
vector<bool> visited;
vector<int> res, tmp;
int start, dest;
int minCost, minDist, currCost, currDist;

void dfs(int origin, int currCost, int currDist){
	visited[origin] = true;
	tmp.push_back(origin);

	if(currDist > minDist) goto ret;
	if(currDist == minDist && currCost > minCost) goto ret;

	if(origin == dest){
		if(currDist < minDist ||
		  (currDist == minDist && currCost < minCost)){
			minDist = currDist;
			minCost = currCost;
			res.assign(tmp.begin(), tmp.end());
		}
		goto ret;
	}

	for(edge e : graph[origin])
		if(!visited[e.id])
			dfs(e.id, currCost + e.cost, currDist + e.dist);

	ret:
	tmp.pop_back();
	visited[origin] = false;
}

int main(){
	int N, M;
	int one, two, cost, dist;
	scanf("%d %d %d %d", &N, &M, &start, &dest);
	graph = vector<vector<edge>>(N);
	visited = vector<bool>(N, false);
	for(int ix = 0; ix != M; ++ix){
		scanf("%d %d %d %d", &one, &two, &dist, &cost);
		graph[one].emplace_back(two, dist, cost);
		graph[two].emplace_back(one, dist, cost);
	}

	minDist = minCost = 0x7fffffff;
	dfs(start, 0, 0);
	for(int e : res)
		printf("%d ", e);
	printf("%d %d", minDist, minCost);
	return 0;
}
