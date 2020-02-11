#include <vector>
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

/*
 * 这个题的逻辑还是有一点复杂的，细节方面的处理需要比较
 * 仔细才行。我看第一个测试样例，所有房屋到 G1 的路径长
 * 度之和是 13，所以 aver = 13 / 4 = 3.25，精确到小数
 * 点后一位，样例给出的答案是 3.3。
 * 
 * 然而我用 printf(".1%f", avg) 给出的答案却是 3.2。
 * 我一时想不出怎么修改这个代码，使得可以严格『四舍五入』，
 * 于是首先尝试提交了一下，然后就通过了......我佛了。
 */

#define INF (0x3fff)

struct edge{
	int id;
	int length;

	edge(int id, int len): id(id), length(len){}
};

int N, range;

vector<vector<edge>> graph;
vector<int> dist;
vector<bool> visited;

bool dijkstra(int origin, int &currMin, int &currAver){
	dist[origin] = 0;

	int curr = origin, minDist, min;
	while(true){
		visited[curr] = true;
		for(edge e: graph[curr])
			if(dist[curr] + e.length < dist[e.id])
				dist[e.id] = dist[curr] + e.length;
		minDist = INF, min = -1;
		for(int ix = 1; ix != dist.size(); ++ix){
			if(!visited[ix] && dist[ix] < minDist){
				minDist = dist[ix];
				min = ix;
			}
		}
		curr = min;
		if(curr == -1) break;
		if(curr <= N && dist[curr] > range) return false;
	}
	currAver = dist[1], currMin = dist[1];
	for(int ix = 2; ix <= N; ++ix){
		currAver += dist[ix];
		if(dist[ix] < currMin)
			currMin = dist[ix];
	}
	return true;
}

int main(){
	int M, K;
	cin >> N >> M >> K >> range;
	graph = vector<vector<edge>>(N + M + 1);
	visited = vector<bool>(N + M + 1);
	dist = vector<int>(N + M + 1);

	int one, two, len;
	string left,right;
	for(int ix = 0; ix != K; ++ix){
		cin >> left >> right >> len;
		if(left[0] == 'G')
			one = N + stoi(left.substr(1));
		else one = stoi(left);
		if(right[0] == 'G')
			two = N + stoi(right.substr(1));
		else two = stoi(right);
		graph[one].emplace_back(two, len);
		graph[two].emplace_back(one, len);
	}

	int currAver, currMin, aver, min = 0;
	int res = -1;
	for(int ix = N + 1; ix <= M + N; ++ix){
		for(int ix = 1; ix != visited.size(); ++ix){
			visited[ix] = false;
			dist[ix] = INF;
		}
		if(dijkstra(ix, currMin, currAver)){
			if(currMin > min || (currMin == min && currAver < aver)){
				res = ix;
				min = currMin;
				aver = currAver;
			}
		}
	}
	double avg = (double)aver / N;
	if(res == -1) cout << "No Solution" << endl;
	else{
		cout << 'G' << res - N << endl;
		printf("%d.0 %.1f\n", min, avg);
	}
	return 0;
}
