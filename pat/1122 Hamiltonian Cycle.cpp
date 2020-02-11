#include <vector>
#include <cstdio>
using namespace std;

/*
 * 关于哈密尔顿环路我都快忘了，它的定义是，除了首位节点外，
 * 经过图中所有其他节点一次且仅一次的简单环路。
 */

vector<vector<bool>> graph(201, vector<bool>(201));
vector<bool> visited(201);

int main(){
	int N, M, one, two;
	scanf("%d %d", &N, &M);
	for(int ix = 0; ix != M; ++ix){
		scanf("%d %d", &one, &two);
		graph[one][two] = true;
		graph[two][one] = true;
	}
	int K, count, src, prev, curr, dest;
	bool flag;
	scanf("%d", &K);
	for(int ix = 0; ix != K; ++ix){
		flag = true;
		for(int ix = 1; ix != N + 1; ++ix)
            visited[ix] = false;
		scanf("%d %d", &count, &src);
		if(count != N + 1) flag = false;
		visited[src] = true;
		prev = src;
		while(--count > 1){
			scanf("%d", &curr);
			if(!flag) continue;
			if(!graph[prev][curr] || visited[curr])
				flag = false;
			visited[curr] = true;
			prev = curr;
		}
		scanf("%d", &dest);
		if(!graph[prev][dest] || src != dest)
			flag = false;
		if(!flag) printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}
