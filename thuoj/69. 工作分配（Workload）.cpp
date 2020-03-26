#include <cstdio>
#include <cstring>

#define INF (0x7fffffff)

bool visited[15];
int  time[15][15];

int mintime = INF, n;

void dfs(int origin, int depth, int currtime){
	visited[origin] = true;
	currtime += time[depth][origin];

	bool haschild = false;
	if(currtime > mintime) goto ret;
	for(int ix = 0; ix != n; ++ix)
		if(!visited[ix]){
			haschild = true;
			dfs(ix, depth + 1, currtime);
		}
	if(!haschild && currtime < mintime)
		mintime = currtime;

	ret:
	currtime -= time[depth][origin];
	visited[origin] = false;
}

int main(){
	scanf("%d", &n);
	memset(visited, 0, sizeof(visited));
	for(int ix = 0; ix != n; ++ix){
		for(int jx = 0; jx != n; ++jx)
			scanf("%d", &time[ix][jx]);
	}
	for(int ix = 0; ix != n; ++ix)
		dfs(ix, 0, 0);
	printf("%d\n", mintime);
	return 0;
}
