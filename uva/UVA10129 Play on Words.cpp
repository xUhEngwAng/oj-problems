#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

vector<int> head(26), tail(26);
vector<set<int>> graph;
vector<bool> visited(26);

void dfs(int src){
	visited[src] = true;
	for(int e : graph[src])
		if(!visited[e]) 
			dfs(e);
}

int main(){
	//freopen("1.out", "w", stdout);
	int T, N, diff, src, ix;
	bool isconnect;
	cin >> T;
	string str;
	while(T--){
		cin >> N;
		fill(head.begin(), head.end(), 0);
		fill(tail.begin(), tail.end(), 0);
		fill(visited.begin(), visited.end(), false);
		graph.clear();
		graph.resize(26);
		for(int ix = 0; ix != N; ++ix){
			cin >> str;
			head[str.front() - 'a']++;
			tail[str.back() - 'a']++;
			graph[str.front() - 'a'].insert(str.back() - 'a');
		}
		diff = 0;
		ix = 0;
		while(!head[ix]) ++ix;
		src = ix;
		for(;ix != 26; ++ix){
			if(tail[ix] < head[ix]) src = ix;
			diff += abs(head[ix] - tail[ix]);
		}
		
		dfs(src);
		isconnect = true;
		for(int ix = 0; ix != 26; ++ix){
			if(!head[ix] && !tail[ix]) continue;
			if(!visited[ix]){
				isconnect = false;
				break;
			}
		}

		if(diff > 2 || !isconnect) 
			cout << "The door cannot be opened." << endl;
		else 
			cout << "Ordering is possible." << endl;
	}
	return 0;
}
