#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * 这个题我的思路就是管理一个和原始表格规模相同的表格，
 * 每一个单元格存储的是其当前的位置。这样只需要对整个表
 * 都进行操作，就得到了所有原始单元格的最终位置，每一个
 * 查询在 O(1) 时间内就可以完成了。
 *
 * 对于四个行列操作，我的做法是把所有单元格行（列）变化量
 * 保存起来，进行一次遍历即可。这里需要注意将所有行列一起
 * 插入和分别插入（删除）其结果是不同的。
 *
 * 对于交换操作，按理说应该是比较简单的，我一开始却做错了。
 * 需要注意到，被交换的两个位置未必会在管理的表格中出现，
 * 有可能只出现一个，有可能一个都不出现。
 */

struct Posi{
	int row;
	int col;
};

vector<vector<Posi>> posi;
vector<int> cnt(51);

void deleteRow(const vector<int> &para){
	int m = posi.size(), n = posi[0].size();
	fill(cnt.begin(), cnt.end(), 0);
	for(int e : para) cnt[e] = 1;
	for(int ix = 1; ix != 51; ++ix)
		cnt[ix] += cnt[ix - 1];
	for(int e : para) cnt[e] = e + 1;
	for(int ix = 1; ix != m; ++ix)
		for(int jx = 1; jx != n; ++jx){
            if(posi[ix][jx].row == -1) continue;
			posi[ix][jx].row -= cnt[posi[ix][jx].row];
			if(posi[ix][jx].row == -1) posi[ix][jx].col = -1;
		}
}

void deleteCol(const vector<int> &para){
	int m = posi.size(), n = posi[0].size();
	fill(cnt.begin(), cnt.end(), 0);
	for(int e : para) cnt[e] = 1;
	for(int ix = 1; ix != 51; ++ix)
		cnt[ix] += cnt[ix - 1];
	for(int e : para) cnt[e] = e + 1;
	for(int ix = 1; ix != m; ++ix)
		for(int jx = 1; jx != n; ++jx){
            if(posi[ix][jx].col == -1) continue;
			posi[ix][jx].col -= cnt[posi[ix][jx].col];
			if(posi[ix][jx].col == -1) posi[ix][jx].row = -1;
		}
}

void insertRow(const vector<int> &para){
	int m = posi.size(), n = posi[0].size();
	fill(cnt.begin(), cnt.end(), 0);
	for(int e : para) cnt[e] = 1;
	for(int ix = 1; ix != 51; ++ix)
        cnt[ix] += cnt[ix - 1];
	for(int ix = 1; ix != m; ++ix)
		for(int jx = 1; jx != n; ++jx){
            if(posi[ix][jx].row == -1) continue;
			posi[ix][jx].row += cnt[posi[ix][jx].row];
		}
}

void insertCol(const vector<int> &para){
	int m = posi.size(), n = posi[0].size();
	fill(cnt.begin(), cnt.end(), 0);
	for(int e : para) cnt[e] = 1;
	for(int ix = 1; ix != 51; ++ix)
        cnt[ix] += cnt[ix - 1];
	for(int ix = 1; ix != m; ++ix)
		for(int jx = 1; jx != n; ++jx){
            if(posi[ix][jx].col == -1) continue;
			posi[ix][jx].col += cnt[posi[ix][jx].col];
		}
}

void exchange(int r1, int c1, int r2, int c2){
	int row1, col1, row2, col2;
	int m = posi.size(), n = posi[0].size();
	for(int ix = 1; ix != m; ++ix){
		for(int jx = 1; jx != n; ++jx){
			if(posi[ix][jx].row == r1 && posi[ix][jx].col == c1){
				posi[ix][jx].row = r2;
				posi[ix][jx].col = c2;
			}
			else
			if(posi[ix][jx].row == r2 && posi[ix][jx].col == c2){
				posi[ix][jx].row = r1;
				posi[ix][jx].col = c1;
			}
		}
	}
}

int main(){
	//freopen("1.out", "w", stdout);
	int n, r, c, num, cnt = 0;
	int r1, c1, r2, c2, curr;
	char command[3];
	vector<int> para;
	while(scanf("%d %d", &r, &c) == 2){
		if(r == 0) break;
		if(cnt != 0) printf("\n");
		printf("Spreadsheet #%d\n", ++cnt);
		posi = vector<vector<Posi>>(r + 1, vector<Posi>(c + 1));
		for(int ix = 1; ix <= r; ++ix)
			for(int jx = 1; jx <= c; ++jx){
				posi[ix][jx].row = ix;
				posi[ix][jx].col = jx;
			}
		scanf("%d", &n);
		while(n--){
			scanf("%s", command);
			if(command[0] == 'E'){
				scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
				exchange(r1, c1, r2, c2);
			}
			else{
				scanf("%d", &num);
				para.resize(num);
				for(int ix = 0; ix != num; ++ix)
					scanf("%d", &para[ix]);
				if(!strcmp(command, "DR")) deleteRow(para);
				else
				if(!strcmp(command, "DC")) deleteCol(para);
				else
				if(!strcmp(command, "IR")) insertRow(para);
				else                       insertCol(para);
			}
			/*
			for(auto entry : posi){
                for(auto e : entry)
                    printf("%d,%d  ", e.row, e.col);
                printf("\n");
            }*/
		}
		scanf("%d", &n);
		while(n--){
			scanf("%d %d", &r, &c);
			printf("Cell data in (%d,%d) ", r, c);
			if(posi[r][c].row == -1) printf("GONE\n");
			else
				printf("moved to (%d,%d)\n", posi[r][c].row, posi[r][c].col);
		}
	}
	return 0;
}
