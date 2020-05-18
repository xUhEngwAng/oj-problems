#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

struct entry{
	int row, col, value;
	entry() = default;
	entry(int r, int c, int v): row(r), col(c), value(v){}
};

bool cmp(const entry &one, const entry &two){
	if(one.row == two.row)
		return one.col < two.col;
	return one.row < two.row;
}

int arr[1000][1000];
int row_cnt[1000], col_cnt[1000];
vector<entry> ans;

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	memset(row_cnt, 0, sizeof(row_cnt));
	memset(col_cnt, 0, sizeof(col_cnt));
	for(int ix = 0; ix != n; ++ix)
	for(int jx = 0; jx != m; ++jx){
		scanf("%d", &arr[ix][jx]);
		if(arr[ix][jx]){
			row_cnt[ix]++;
			col_cnt[jx]++;
		}
	}
	/*for(int ix = 0; ix != n; ++ix)
			printf("%d ", row_cnt[ix]);
		printf("\n");
		for(int ix = 0; ix != m; ++ix)
			printf("%d ", col_cnt[ix]);
		printf("tag\n");*/
	bool flag = true;
	int d, cnt, v[2], p[2], curr, first;
	while(flag){
		flag = false;
		for(int ix = 0; ix != n; ++ix){
			if(row_cnt[ix] < 2 || row_cnt[ix] == m) continue;
			flag = true;
			cnt = 0;
			for(int jx = 0; jx != m; ++jx){
				if(arr[ix][jx]){
					v[cnt] = arr[ix][jx];
					p[cnt++] = jx;
					if(cnt == 2) break;
				}
			}
			d = (v[1] - v[0]) / (p[1] - p[0]);
			first = v[0] - p[0] * d;
			for(int jx = 0, curr = first; jx != m; ++jx){
				if(!arr[ix][jx]){
					arr[ix][jx] = curr;
					col_cnt[jx]++;
					ans.emplace_back(ix, jx, curr);
				}
				curr += d;
			}
			row_cnt[ix] = m;
		}
		for(int ix = 0; ix != m; ++ix){
			if(col_cnt[ix] < 2 || col_cnt[ix] == n) continue;
			flag = true;
			cnt = 0;
			for(int jx = 0; jx != n; ++jx){
				if(arr[jx][ix]){
					v[cnt] = arr[jx][ix];
					p[cnt++] = jx;
					if(cnt == 2) break;
				}
			}
			d = (v[1] - v[0]) / (p[1] - p[0]);
			first = v[0] - p[0] * d;
			for(int jx = 0, curr = first; jx != n; ++jx){
				if(!arr[jx][ix]){
					arr[jx][ix] = curr;
					row_cnt[ix]++;
					ans.emplace_back(jx, ix, curr);
				}
				curr += d;
			}
			col_cnt[ix] = n;
		}
		/*for(int ix = 0; ix != n; ++ix)
			printf("%d ", row_cnt[ix]);
		printf("\n");
		for(int ix = 0; ix != m; ++ix)
			printf("%d ", col_cnt[ix]);
		printf("tag\n");*/
	}
	sort(ans.begin(), ans.end(), cmp);
	for(auto e : ans){
		printf("%d %d %d\n", e.row + 1, e.col + 1, e.value);
	}
	return 0;
}
