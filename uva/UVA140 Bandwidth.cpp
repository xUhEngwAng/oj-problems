#include <cstdio>
#include <vector>
#include <set>
#include <cstring>
using namespace std;

/*
 * 这里犯了一个非常愚蠢的错误，我把 MAX 宏写错了！就忘了
 * 这种语法了......要注意啊。
 */

#define INF       (0x7fffffff)
#define MAX(X, Y) ((X) > (Y)? (X): (Y))

int matrix[26][26], min_bandwidth;
bool visited[26];
set<int> nodes_set;
vector<int> nodes, res, tmp;

void dfs(int origin, int prev){
	visited[origin] = true;
	tmp.push_back(origin);

	int bandwidth = 0;
	for(int ix = tmp.size() - 2; ix >= 0; --ix)
		if(matrix[origin][tmp[ix]]){
			//printf("%c %c\n", origin + 'A', tmp[ix] + 'A');
			bandwidth = tmp.size() - ix - 1;
		}
	bandwidth = MAX(bandwidth, prev);
	//printf("%d\n", bandwidth);
	//while(getchar() != '\n');

	if(bandwidth > min_bandwidth) goto ret;
	if(tmp.size() == nodes.size()){
		if(bandwidth < min_bandwidth){
			min_bandwidth = bandwidth;
			res.assign(tmp.begin(), tmp.end());
		}
		goto ret;
	}

	for(int e : nodes)
		if(!visited[e])
			dfs(e, bandwidth);
	ret:
	tmp.pop_back();
	visited[origin] = false;
}

int main(){
	//freopen("1.out", "w", stdout);
	char curr, neighbor;
	while(true){
		curr = getchar();
		if(curr == '#') break;
		memset(matrix, 0, sizeof(matrix));
		nodes_set.clear();
		while(true){
			nodes_set.insert(curr - 'A');
			getchar();
			while(true){
				neighbor = getchar();
				if(neighbor == ';') break;
				if(neighbor == '\n') break;
				nodes_set.insert(neighbor - 'A');
				matrix[curr - 'A'][neighbor - 'A'] = 1;
				matrix[neighbor - 'A'][curr - 'A'] = 1;
			}
			if(neighbor == '\n') break;
			curr = getchar();
		}/*
		for(int ix = 0; ix != 25; ++ix){
			for(int jx = 0; jx != 25; ++jx)
				printf("%d ", matrix[ix][jx]);
			printf("\n");
		}*/
		nodes.assign(nodes_set.begin(), nodes_set.end());
		memset(visited, 0, sizeof(visited));
		min_bandwidth = INF;
		for(int e : nodes)
			dfs(e, 0);
		for(int e : res)
			printf("%c ", e + 'A');
		printf("-> %d\n", min_bandwidth);
	}
	return 0;
}
