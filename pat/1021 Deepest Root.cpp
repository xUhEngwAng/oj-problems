#include <stdio.h>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
using namespace std;
set<int> unvisited;
map<int, set<int>> graph;
int N;
int bfs(int start){
	queue<int> intque;
	int height = 0, count = 0, currcount = 1, nextcount = 0, node;
	intque.push(start);
	while (!intque.empty()) {
		node = intque.front();
		intque.pop();
		if (find(unvisited.begin(), unvisited.end(), node) == unvisited.end()) continue;
		unvisited.erase(node);
		for (auto It = unvisited.begin(); It != unvisited.end(); It++)
			if (find(graph[node].begin(), graph[node].end(), *It) != graph[node].end()) {
				intque.push(*It);
				nextcount += 1;
			}
		count++;
		if (count == currcount) {
			height += 1;
			currcount = nextcount;
			nextcount = 0;
			count = 0;
		}
	}
	return height;
}
int main() {
	int first, second;
	scanf("%d", &N);
	for (int ix = 0; ix != N - 1; ix++) {
		scanf("%d %d", &first, &second);
		graph[first - 1].insert(second - 1);
		graph[second - 1].insert(first - 1);
	}
	queue<int> intque;
	vector<int> root;
	int maxheight = 0, num, height, node;
	for (int ix = 0; ix != N; ix++) {
		num = 1;
		unvisited.clear();
		for (int ix = 0; ix != N; ix++)  unvisited.insert(ix);
		height = bfs(ix);
		while(!unvisited.empty()){
			node = *unvisited.begin();
			bfs(node);
			++num;
		}
		if (num != 1) {
			printf("Error: %d components", num);
			system("pause");
			return 0;
		}
		if (height > maxheight) {
			root.clear();
			root.push_back(ix + 1);
			maxheight = height;
		}
		else if (height == maxheight) root.push_back(ix + 1);
	}
	sort(root.begin(), root.end());
	for_each(root.begin(), root.end(), [](int node) {printf("%d\n", node); });
	system("pause");
	return 0;
}
