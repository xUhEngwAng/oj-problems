#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

struct Posi{
	int row;
	int col;
};

vector<vector<Posi>> posi;

void deleteRow(const vector<int> &para){
	int m = posi.size(), n = posi[0].size();
	vector<int> cnt(51, 0);
	for(int e : para) cnt[e] = 1;
	for(int ix = 1; ix != 51; ++ix)
		cnt[ix] += cnt[ix - 1];
	for(int e : para) cnt[e] = e + 1;
	for(int ix = 1; ix != m; ++ix)
		for(int jx = 1; jx != n; ++jx){
            if(posi[ix][jx].col == -1) continue;
			posi[ix][jx].row -= cnt[posi[ix][jx].row];
			if(posi[ix][jx].row == -1) posi[ix][jx].col = -1;
		}
}

void deleteCol(const vector<int> &para){
	int m = posi.size(), n = posi[0].size();
	vector<int> cnt(51, 0);
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
	vector<int> cnt(51, 0);
	for(int e : para) cnt[e] = 1;
	for(int ix = 1; ix != 51; ++ix)
        cnt[ix] += cnt[ix - 1];
	for(int ix = 1; ix != m; ++ix)
		for(int jx = 1; jx != n; ++jx){
            if(posi[ix][jx].col == -1) continue;
			posi[ix][jx].row += cnt[posi[ix][jx].row];
		}
}

void insertCol(const vector<int> &para){
	int m = posi.size(), n = posi[0].size();
	vector<int> cnt(51, 0);
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
				row1 = ix;
				col1 = jx;
			}
			if(posi[ix][jx].row == r2 && posi[ix][jx].col == c2){
				row2 = ix;
				col2 = jx;
			}
		}
	}
	swap(posi[row1][col1], posi[row2][col2]);
}

int main(){
	int n, r, c, num, cnt = 0;
	int r1, c1, r2, c2, curr;
	char command[3];
	vector<int> para;
	while(scanf("%d %d", &r, &c) == 2){
		if(r == 0 && c == 0) break;
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
			if(!strcmp(command, "EX")){
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
