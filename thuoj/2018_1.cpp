#include <cstdio>
#include <algorithm>
using namespace std;

struct entry{
	int row, col;
	int dir, force;
	int alive = 1;
}info[1000];

int temp[1000], m, n;

void move(int curr){
	if(info[curr].alive == 0) return;
	int dir = info[curr].dir;
	if(dir == 0){
		if(info[curr].row == 1) info[curr].dir = 1;
		else info[curr].row--;
	}else
	if(dir == 1){
		if(info[curr].row == n) info[curr].dir = 0;
		else info[curr].row++;
	}else
	if(dir == 2){
		if(info[curr].col == 1) info[curr].dir = 3;
		else info[curr].col--;
	}
	else{
		if(info[curr].col == m) info[curr].dir = 2;
		else info[curr].col++;
	}
}

bool cmp(int one, int two){
	if(info[one].row == info[two].row){
		if(info[one].col == info[two].col){
			if(info[one].alive == info[two].alive)
				return info[one].force > info[two].force;
			return info[one].alive > info[two].alive;
		}
		return info[one].row < info[two].row;
	}
	return info[one].row < info[two].row;
}

int main(){
	int k, t;
	scanf("%d %d %d", &n, &m, &k);
	for(int ix = 0; ix != k; ++ix){
		scanf("%d %d %d %d", &info[ix].row, &info[ix].col, 
			                 &info[ix].dir, &info[ix].force);
		temp[ix] = ix;
	}
	scanf("%d", &t);
	while(t--){
		for(int ix = 0; ix != k; ++ix)
			move(ix);
		sort(temp, temp + k, cmp);
		for(int ix = 0, jx; ix != k; ix = jx)
			for(jx = ix + 1; jx != k; jx++){
				if(info[temp[ix]].row != info[temp[jx]].row || info[temp[ix]].col != info[temp[jx]].col)
					break;
				info[temp[jx]].alive = 0;
			}
		/*for(int ix = 0; ix != k; ++ix){
			printf("%d: %d %d ", ix + 1, info[ix].row, info[ix].col);
			if(info[ix].alive) printf("alive\n");
			else printf("died\n");
		}*/
	}
	for(int ix = 0; ix != k; ++ix)
		printf("%d %d\n", info[ix].row, info[ix].col);
	return 0;
}
