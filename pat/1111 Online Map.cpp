#include <vector>
#include <cstdio>
#include <algorithm>
using std::vector;

#define INF (0x7fffffff)

/*
 * 这个题一开始是用 dfs 做的（我 dfs 十级爱好者），尽管
 * N 最多只有 500，但是在图相当稠密的情况下，时间复杂度
 * 还是很高的，因此不可避免地超时了。
 *
 * 然后改写成两个 dijkstra 的版本，代码量虽然多了一点，
 * 但是就轻松通过了。这里遇到了一个细节问题，我本来以为
 * vector.resize(cnt, v) 可以将原来的向量赋值为 cnt
 * 个 v 值，然后该接口的含义是将 resize 新增的元素赋
 * 为 v。改用 fill 方法才可以实现我想要的功能。
 */

/*
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
*/
struct node{
	int length = INF;
	int time = INF;
};


int M, N;
int src, dest;
vector<vector<node>> graph(500, vector<node>(500));
vector<int> shortest, fastest, length, time, prev, cnt;
vector<bool> visited;

int dijkstra_shortest(int src){
	length.resize(N, INF);
	time.resize(N, INF);
	prev.resize(N);
	visited.resize(N, false);
	int curr = src, mintime, minlen, next;
	length[curr] = 0, time[curr] = 0;
	while(true){
		visited[curr] = true;
		mintime = minlen = INF;
		for(int ix = 0; ix != N; ++ix){
			if(visited[ix]) continue;
			if(graph[curr][ix].time != INF){
				if(length[curr] + graph[curr][ix].length < length[ix]){
					length[ix] = length[curr] + graph[curr][ix].length;
					time[ix] = time[curr] + graph[curr][ix].time;
					prev[ix] = curr;
				}else
				if(length[curr] + graph[curr][ix].length == length[ix] &&
				   time[curr] + graph[curr][ix].time < time[ix]){
					time[ix] = time[curr] + graph[curr][ix].time;
					prev[ix] = curr;
				}
			}
			if(length[ix] < minlen){
				minlen = length[ix];
				mintime = time[ix];
				next = ix;
			}else
			if(length[ix] == minlen && time[ix] < mintime){
				mintime = time[ix];
				next = ix;
			}
		}
		if(mintime == INF) break;
		curr = next;
	}
	curr = dest;
	while(curr != src){
		shortest.push_back(curr);
		curr = prev[curr];
	}
	return length[dest];
}

int dijkstra_fastest(int src){
	fill(time.begin(), time.end(), INF);
	cnt.resize(N, INF);
	fill(visited.begin() ,visited.end(), false);
	int curr = src, mintime, mincnt, next;
	cnt[curr] = 0, time[curr] = 0;
	while(true){
		visited[curr] = true;
		mintime = mincnt = INF;
		for(int ix = 0; ix != N; ++ix){
			if(visited[ix]) continue;
			if(graph[curr][ix].time != INF){
				if(time[curr] + graph[curr][ix].time < time[ix]){
					time[ix] = time[curr] + graph[curr][ix].time;
					cnt[ix] = cnt[curr] + 1;
					prev[ix] = curr;
				}else
				if(time[curr] + graph[curr][ix].time == time[ix] &&
				   cnt[curr] + 1 < cnt[ix]){
					cnt[ix] = cnt[curr] + 1;
					prev[ix] = curr;
				}
			}
			if(time[ix] < mintime){
				mintime = time[ix];
				mincnt = cnt[ix];
				next = ix;
			}else
			if(time[ix] == mintime && cnt[ix] < mincnt){
				mincnt = cnt[ix];
				next = ix;
			}
		}
		if(mintime == INF) break;
		curr = next;
	}
	curr = dest;
	while(curr != src){
		fastest.push_back(curr);
		curr = prev[curr];
	}
	return time[dest];
}

int main(){
	int oneway, v1, v2, len, time;
	scanf("%d %d", &N, &M);
	for(int ix = 0; ix != M; ++ix){
		scanf("%d %d %d %d %d", &v1, &v2, &oneway, &len, &time);
		graph[v1][v2].length = len;
		graph[v1][v2].time = time;
		if(!oneway){
			graph[v2][v1].length = len;
			graph[v2][v1].time = time;
		}
	}
	scanf("%d %d", &src, &dest);
	int dist = dijkstra_shortest(src);
	time = dijkstra_fastest(src);
	if(shortest == fastest){
		printf("Distance = %d; Time = %d: %d", dist, time, src);
		for(int ix = shortest.size() - 1; ix >= 0; --ix)
			printf(" -> %d", shortest[ix]);
		printf("\n");
	}
	else{
		printf("Distance = %d: %d", dist, src);
		for(int ix = shortest.size() - 1; ix >= 0; --ix)
			printf(" -> %d", shortest[ix]);
		printf("\n");
		printf("Time = %d: %d", time, src);
		for(int ix = fastest.size() - 1; ix >= 0; --ix)
			printf(" -> %d", fastest[ix]);
		printf("\n");
	}
	return 0;
}
