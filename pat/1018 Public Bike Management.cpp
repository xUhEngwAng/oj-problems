#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#define INF 99999999
using namespace std;
int capacity;
vector<int> temppath, path, weight;
vector<vector<int>> paths;
int send, collect, lack, minsend = INF, mincollect = INF;
void dfs(int start){
	temppath.push_back(start);
	if(start == 0){//hit the bottom
		send = collect = 0;
		for(auto It = temppath.rbegin() + 1; It != temppath.rend(); It++){
			lack = capacity / 2 - weight[*It];
			if(lack > 0){
				if(lack >= collect){
					send += lack - collect;
					collect = 0;
				}
				else collect -= lack;
			}
			else collect += weight[*It] - capacity / 2;
		}
		if(send < minsend){
			minsend = send;
			mincollect = collect;
			path.assign(temppath.begin(), temppath.end());
		}else 
		if(send == minsend && collect < mincollect){
			mincollect = collect;
			path.assign(temppath.begin(), temppath.end());
		}
		temppath.pop_back();
		return;
	}
	for (auto It = paths[start].begin(); It != paths[start].end(); It++)
		dfs(*It);
	temppath.pop_back();
}
int main(){
	int N, M, target;
	scanf("%d %d %d %d", &capacity, &N, &target, &M);
	vector<vector<int>> roads(N + 1, vector<int>(N + 1, INF));
	vector<int> dist(N + 1, INF);
	weight.resize(N + 1);
	for (int ix = 1; ix != N + 1; ix++)
		scanf("%d", &weight[ix]);
	int first, second, len;
	for(int ix = 0; ix != M; ix++){
		scanf("%d %d %d", &first, &second, &len);
		roads[first][second] = len;
		roads[second][first] = len;
	}
	set<int> unvisited;
	for (int ix = 0; ix != N + 1; ix++)
		unvisited.insert(ix);
	dist[0] = 0;
	paths.resize(N + 1);
	int minlen, via;
	while(!unvisited.empty()){//dijkstra
		minlen = INF;
		for(auto It = unvisited.cbegin(); It != unvisited.cend(); It++){
			if(dist[*It] < minlen){
				minlen = dist[*It];
				via = *It;
			}
		}
		unvisited.erase(via);
		for (auto It = unvisited.cbegin(); It != unvisited.cend(); It++){
			if(dist[via] + roads[via][*It] < dist[*It]){
				dist[*It] = dist[via] + roads[via][*It];
				paths[*It].clear();
				paths[*It].push_back(via);
			}
			else if (dist[via] + roads[via][*It] == dist[*It]) paths[*It].push_back(via);
		}
	}
	dfs(target);
	printf("%d 0", minsend);
	for_each(path.rbegin() + 1, path.rend(), [](int node) {printf("->%d", node); });
	printf(" %d", mincollect);
	system("pause");
	return 0;
}
