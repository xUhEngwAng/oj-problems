#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

/*
 * 这个题确实非常难，应该是最短路径里面最难的情况了，又给
 * 了两个附加判断方案，又要求路径最短的路径条数，还要求路
 * 径本身，用 dijkstra 写的话要好好注意各种细节，感觉还挺
 * 复杂的。
 *
 * 所以我又偷懒了，因为看到数据量不大，N <= 200，我就直接写
 * 了一个 dfs 就完事儿了，实际上这个 dfs 还是有一点复杂的。
 */

#define INF (0x7fffffff)

struct edge{
	string dest;
	int cost;

	edge(string str, int c): dest(str), cost(c){}
};

struct vertex{
	int happiness;
	bool visited = false;
	vector<edge> edges;

	vertex(int happy = 0): happiness(happy){}
};

map<string, vertex> graph;
vector<string> path, res;
const string dest = "ROM";
int num, minCost, maxHappiness, minCnt;

void dfs(string origin, int currCost, int currhapp){
	path.push_back(origin);
	graph[origin].visited = true;

	if(currCost > minCost)
		goto ret;

	if(origin == dest){
		if(currCost < minCost){
			minCnt = path.size();
			minCost = currCost;
			maxHappiness = currhapp;
			num = 1;
			res.assign(path.begin(), path.end());
		}else
		if(currCost == minCost){
			num++;
			if(currhapp > maxHappiness){
				minCnt = path.size();
				maxHappiness = currhapp;
				res.assign(path.begin(), path.end());
			}else
			if(currhapp == maxHappiness && path.size() < minCnt){
				minCnt = path.size();
				res.assign(path.begin(), path.end());
			}
		}
		goto ret;
	}

	for(edge e : graph[origin].edges){
		if(!graph[e.dest].visited)
			dfs(e.dest, currCost + e.cost,
				currhapp + graph[e.dest].happiness);
	}
	ret:
	path.pop_back();
	graph[origin].visited = false;
}


int main(){
	int N, K, currhapp, cost;
	string start, one, two;
	cin >> N >> K >> start;
	graph[start] = vertex(0);
	for(int ix = 1; ix != N; ++ix){
		cin >> one >> currhapp;
		graph[one] = vertex(currhapp);
	}
	for(int ix = 0; ix != K; ++ix){
		cin >> one >> two >> cost;
		graph[one].edges.emplace_back(two, cost);
		graph[two].edges.emplace_back(one, cost);
	}

	minCost = minCnt = INF,num = maxHappiness = 0;
	dfs(start, 0, 0);
	cout << num << ' ' << minCost << ' ' << maxHappiness << ' '
	     << maxHappiness / (res.size() - 1) << endl;
	cout << res[0];
	for(int ix = 1; ix != res.size(); ++ix)
		cout << "->" << res[ix];
	cout << endl;
	return 0;
}
