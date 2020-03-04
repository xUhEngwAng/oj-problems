#include <vector>
#include <cstdio>
#include <queue>
using namespace std;

/*
 * 我一开始确实没有看懂此题的题意是什么，还是看了《算法笔记》的
 * 解说，才明白原来是一个 bfs。感觉在编码上并不存在什么困难吧，
 * 中规中矩一个题，就做一个立体的 bfs 即可。
 */

int M, N, L, T;
vector<vector<vector<bool>>> cube;

struct node{
	int x, y, z;
	node() = default;
	node(int x, int y, int z): x(x), y(y), z(z){}
};

int bfs(int x, int y, int z){
	queue<node> q;
	int cnt = 0;
	q.push(node(x, y, z));
	cube[x][y][z] = false;
	node tmp;
	while(!q.empty()){
		tmp = q.front();
		q.pop();
		if(tmp.x > 0 && cube[tmp.x-1][tmp.y][tmp.z]){
			q.push(node(tmp.x-1, tmp.y, tmp.z));
			cube[tmp.x-1][tmp.y][tmp.z] = false;
		}
		if(tmp.x < L - 1 && cube[tmp.x+1][tmp.y][tmp.z]){
			q.push(node(tmp.x+1, tmp.y, tmp.z));
			cube[tmp.x+1][tmp.y][tmp.z] = false;
		}
		if(tmp.y > 0 && cube[tmp.x][tmp.y-1][tmp.z]){
			q.push(node(tmp.x, tmp.y-1, tmp.z));
			cube[tmp.x][tmp.y-1][tmp.z] = false;
		}
		if(tmp.y < M - 1 && cube[tmp.x][tmp.y+1][tmp.z]){
			q.push(node(tmp.x, tmp.y+1, tmp.z));
			cube[tmp.x][tmp.y+1][tmp.z] = false;
		}
		if(tmp.z > 0 && cube[tmp.x][tmp.y][tmp.z-1]){
			q.push(node(tmp.x, tmp.y, tmp.z-1));
			cube[tmp.x][tmp.y][tmp.z-1] = false;
		}
		if(tmp.z < N - 1 && cube[tmp.x][tmp.y][tmp.z+1]){
			q.push(node(tmp.x, tmp.y, tmp.z+1));
			cube[tmp.x][tmp.y][tmp.z+1] = false;
		}
		++cnt;
	}
	return cnt;
}

int main(){
	int curr;
	scanf("%d %d %d %d", &M, &N, &L, &T);
	cube = vector<vector<vector<bool>>>(L,
		          vector<vector<bool>>(M, vector<bool>(N)));
	for(int ix = 0; ix != L; ++ix)
		for(int jx = 0; jx != M; ++jx)
			for(int kx = 0; kx != N; ++kx){
				scanf("%d", &curr);
				if(curr) cube[ix][jx][kx] = true;
			}
	int cnt, volume = 0;
	for(int ix = 0; ix != L; ++ix)
		for(int jx = 0; jx != M; ++jx)
			for(int kx = 0; kx != N; ++kx){
				if(cube[ix][jx][kx]){
					cnt = bfs(ix, jx, kx);
                    //printf("%d\n", cnt);
                    if(cnt >= T) volume += cnt;
				}
			}
	printf("%d\n", volume);
	return 0;
}
