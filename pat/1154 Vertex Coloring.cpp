#include <stdio.h>
#include <map>
#include <set>
#include <queue>
#include <vector>
using namespace std;
int main_past_version(){
	int N, M;
	scanf("%d %d", &N, &M);
	map<int, set<int>> edges;
	int first, second;
	for(int ix = 0; ix != M; ix++){
		scanf("%d %d", &first, &second);
		edges[first].insert(second);
		edges[second].insert(first);
	}
	int K, node;
	vector<int> coloring(N);
	set<int> unvisited, colors;
	queue<int> intque;
	scanf("%d", &K);
	for(int ix = 0; ix != K; ix++){
		unvisited.clear();
		while (!intque.empty()) intque.pop();
		for (int jx = 0; jx != N; jx++) {
			scanf("%d", &coloring[jx]);
			unvisited.insert(jx);
		}
		while(!unvisited.empty()){
			node = *unvisited.begin();
			intque.push(node);
			while(!intque.empty()){//bfs
				node = intque.front();
				unvisited.erase(node);
				intque.pop();
				if (edges.find(node) == edges.end()) continue;
				for(auto It = edges[node].begin(); It != edges[node].end(); It++){
					if(unvisited.find(*It) != unvisited.end()){
						if (coloring[node] != coloring[*It]) intque.push(*It);
						else{
							printf("No\n");
							goto endloop;
						}
					}
				}
			}
		}
		colors.clear();
		for_each(coloring.begin(), coloring.end(), [&colors](int color) {colors.insert(color); });
		printf("%d-coloring\n", colors.size());
		endloop:;
	}
	system("pause");
	return 0;
}

struct node{
	int first, second;
};
int main(){
	int N, M;
	scanf("%d %d", &N, &M);
	vector<node> edges(M);
	for(int ix = 0; ix != M; ix++){
		scanf("%d %d", &edges[ix].first, &edges[ix].second);
	}
	int K;
	scanf("%d", &K);
	vector<int> coloring(N);
	set<int> colors;
	int flag;
	for(int ix = 0; ix != K; ix++){
		colors.clear();
		for(int jx = 0; jx != N; jx++){
			scanf("%d", &coloring[jx]);
			colors.insert(coloring[jx]);
		}
		flag = 1;
		for(auto It = edges.begin(); It != edges.end(); It++){
			if (coloring[It->first] == coloring[It->second]){
				flag = 0;
				break;
			}
		}
		if(flag) printf("%d-coloring\n", colors.size());
		else printf("No\n");
	}
	system("pause");
	return 0;
}