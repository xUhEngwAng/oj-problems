#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

#define INF (0x7fffffff)

int main(){
	int N, M;
	scanf("%d %d", &N, &M);
	vector<vector<int>> matrix(N + 1, vector<int>(N + 1));
	int one, two, dist;
	for(int ix = 0; ix != M; ++ix){
		scanf("%d %d %d", &one, &two, &dist);
		matrix[one][two] = dist;
		matrix[two][one] = dist;
	}
	int K, num, mindist = INF, minIdx;
	scanf("%d", &K);
	bool iscycle;
	vector<int> path;
	vector<bool> visited(N + 1);
	for(int count = 1; count <= K; ++count){
		dist    = 0;
		iscycle = true;
		scanf("%d", &num);
		while(num--){
			scanf("%d", &one);
			path.push_back(one);
		}
		for(int ix = 0; ix < path.size() - 1; ++ix){
			visited[path[ix]] = true;
			if(matrix[path[ix]][path[ix + 1]] == 0){
				iscycle = false;
				break;
			}
			dist += matrix[path[ix]][path[ix + 1]];
		}
		if(!iscycle)
			printf("Path %d: NA (Not a TS cycle)\n", count);
		else{
			for(int ix = 1; ix <= N; ++ix)
				if(!visited[ix]){
					iscycle = false;
					break;
				}
			if(path.front() != path.back()) iscycle = false;
			if(!iscycle)
				printf("Path %d: %d (Not a TS cycle)\n", count, dist);
			else{
				if(path.size() == N + 1)
					printf("Path %d: %d (TS simple cycle)\n", count, dist);
				else
					printf("Path %d: %d (TS cycle)\n", count, dist);
				if(dist < mindist){
					mindist = dist;
					minIdx = count;
				}
			}
		}
		path.clear();
		fill(visited.begin(), visited.end(), false);
	}
	printf("Shortest Dist(%d) = %d\n", minIdx, mindist);
	return 0;
}
