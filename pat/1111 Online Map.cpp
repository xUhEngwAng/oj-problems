#include <vector>
#include <cstdio>
using namespace std;

#define INF (0x7fffffff)

struct street{
	int num;
	int dist;
	int time;
	street(int num = 0, int len = 0, int t = 0):
	num(num), dist(len), time(t){}
};

vector<vector<street>> graph;
vector<bool> visitd;
vector<int> spath, fpath, currpath;
int src, dest, mindist, mindtime, mintime, mincnt;

void dfs(int src, int dist, int time, int cnt){
	visitd[src] = true;
	currpath.push_back(src);

	if(dist > mindist && time > mintime) goto ret;
	if(src == dest){
		if(dist < mindist || (dist == mindist && time < mindtime)){
			mindist = dist;
			mindtime = time;
			spath.assign(currpath.begin(), currpath.end());
		}
		if(time < mintime || (time == mintime && cnt < mincnt)){
			mintime = time;
			mincnt = cnt;
			fpath.assign(currpath.begin(), currpath.end());
		}
		goto ret;
	}

	for(street s : graph[src]){
		if(!visitd[s.num])
			dfs(s.num, dist + s.dist, time + s.time, cnt + 1);
	}
	ret:
	visitd[src] = false;
	currpath.pop_back();
}

int main(){
	int N, M;
	int oneway, v1, v2, len, time;
	scanf("%d %d", &N, &M);
	graph = vector<vector<street>>(N);
	visitd = vector<bool>(N, false);
	for(int ix = 0; ix != M; ++ix){
		scanf("%d %d %d %d %d", &v1, &v2, &oneway, &len, &time);
		graph[v1].emplace_back(v2, len, time);
		if(!oneway)
			graph[v2].emplace_back(v1, len, time);
	}
	scanf("%d %d", &src, &dest);
	mindist = mintime = mincnt = INF;
	dfs(src, 0, 0, 1);
	if(spath == fpath){
		printf("Distance = %d; Time = %d: %d", mindist, mintime, src);
		for(int ix = 1; ix != spath.size(); ++ix)
			printf(" -> %d", spath[ix]);
		printf("\n");
	}
	else{
		printf("Distance = %d: %d", mindist, src);
		for(int ix = 1; ix != spath.size(); ++ix)
			printf(" -> %d", spath[ix]);
		printf("\n");

		printf("Time = %d: %d", mintime, src);
		for(int ix = 1; ix !=fpath.size(); ++ix)
			printf(" -> %d", fpath[ix]);
		printf("\n");
	}
	return 0;
}
