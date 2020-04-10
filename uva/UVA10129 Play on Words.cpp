#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

/*
 * 此题我觉得非常巧妙，是用欧拉环路来做的。具体说来，将26个
 * 可能出现的字符作为图中的节点，对于每一个单词，即建立了
 * 从首字符到尾字符的一条路径。这个题就是要找对于这样一张图，
 * 是否存在一条欧拉路径。
 *
 * 我一开始的做法只是分别将首尾字符出现的数量各自存储在两个
 * hashtable 当中，然后判断两者的差距是否 <= 2。然而考虑下
 * 面一种情况: aa bb，此时两个 hashtable 完全相同，而这个
 * 输入则是不可行的。
 *
 * 究其原因，是我忽略了存在欧拉环路的充要条件，乃是
 *
 * 1. 除了起点终点外，所有其他节点的入度都等于出度。起点可以
 *    出度比入度大一，终点反之。
 * 2. 图是连通的。
 *
 * 上述情况正是因为图不连通而造成的。 
 */

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
