#include <stdio.h>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
using namespace std;
int main(){
	int N, M, K;
	scanf("%d %d %d", &N, &M, &K);
	vector<vector<int>> highways(N, vector<int>(N));
	int first, second, lost;
	for (int ix = 0; ix != M; ix++){
		scanf("%d %d", &first, &second);
		highways[first-1][second-1] = 1;
		highways[second-1][first-1] = 1;
	}
	queue<int> intque;
	set<int> unvisited;
	int count, pos;
	for (int ix = 0; ix != K; ix++) {
		count = 0;
		unvisited.clear();
		for (int ix = 0; ix != N; ix++)
			unvisited.insert(ix);
		scanf("%d", &lost);
		lost = lost - 1;
		unvisited.erase(lost);
		while (!unvisited.empty()) {
			pos = *unvisited.begin();
			intque.push(pos);
			while(!intque.empty()){//bfs
				pos = intque.front();
				intque.pop();
				if (unvisited.find(pos) != unvisited.end()) {
					unvisited.erase(pos);
					for(int jx = 0; jx != N; jx++){
						if (highways[pos][jx]) intque.push(jx);
					}
				}
			}
			count += 1;	
		}
		printf("%d\n", count - 1);
	}
	system("pause");
	return 0;
}