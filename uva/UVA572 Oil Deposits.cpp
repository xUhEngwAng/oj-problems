#include <queue>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

vector<vector<bool>> visited;
vector<string> map;

struct Pos{
	int row;
	int col;
};

void bfs(int row, int col){
	queue<Pos> q;
	int xpos, ypos;
	visited[row][col] = true;
	Pos tmp;
	tmp.row = row;
	tmp.col = col;
	q.push(tmp);
	while(!q.empty()){
		tmp = q.front();
		q.pop();
		xpos = tmp.col;
		ypos = tmp.row;
		for(int ix = xpos - 1; ix <= xpos + 1; ++ix){
			if(ix < 0 || ix >= map[0].size()) continue;
			for(int jx = ypos - 1; jx <= ypos + 1; ++jx){
				if(jx < 0 || jx >= map.size()) continue;
				if(map[jx][ix] == '@' && !visited[jx][ix]){
					visited[jx][ix] = true;
					tmp.row = jx;
					tmp.col = ix;
					q.push(tmp);
				}
			}
		}
	}
}

int main(){
	int m, n, res;
	string str;
	while(true){
		cin >> m >> n;
		if(m == 0) break;
		map.resize(m);
		for(int ix = 0; ix != m; ++ix)
			cin >> map[ix];
		visited = vector<vector<bool>>(m, vector<bool>(n));
		res = 0;
		for(int ix = 0; ix != m; ++ix)
			for(int jx = 0; jx != n; ++jx)
				if(map[ix][jx] == '@' && !visited[ix][jx]){
					bfs(ix, jx);
					++res;
				}
		cout << res << endl;
	}
	return 0;
}
