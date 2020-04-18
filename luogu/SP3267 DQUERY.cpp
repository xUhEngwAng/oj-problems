#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#pragma GCC optimize(2)
using namespace std;

struct query{
	int left, right, id;
}q[200000];
int n, m, res;
int grp[30001];
int num[30001];
int ans[200000];
int cnt[1000001];

bool cmp(const query &one, const query &two){
	if(grp[one.left] == grp[two.left]){
		if(grp[one.left] & 1) return one.right < two.right;
		else return one.right > two.right;
	}
	return grp[one.left] < grp[two.left];
}

void add(int pos){
	if(!cnt[num[pos]]) res++;
	cnt[num[pos]]++;
}

void del(int pos){
	cnt[num[pos]]--;
	if(!cnt[num[pos]]) --res;
}

int main(){
	scanf("%d", &n);
	int group_size = sqrt(n + 0.5);
	int group_num  = n / group_size + 1;
    for(int ix = 1; ix <= group_num; ++ix)
    for(int jx = 1 + (ix-1) * group_size; jx <= ix * group_size && jx <= n; ++jx)
        grp[jx] = ix;
	for(int ix = 1; ix <= n; ++ix)
		scanf("%d", num + ix);
	scanf("%d", &m);
	memset(cnt, 0, sizeof(cnt));
	for(int ix = 0; ix != m; ++ix){
		scanf("%d %d", &q[ix].left, &q[ix].right);
		q[ix].id = ix;
	}
	sort(q, q + m, cmp);
	int l = 1, r = 0, ql, qr;
	res = 0;
	for(int ix = 0; ix != m; ++ix){
		ql = q[ix].left;
		qr = q[ix].right;
		while(l < ql) res -= !--cnt[num[l++]];
        while(l > ql) res += !cnt[num[--l]]++;
        while(r < qr) res += !cnt[num[++r]]++;
        while(r > qr) res -= !--cnt[num[r--]];
		ans[q[ix].id] = res;
		/*
		for(int ix = 1; ix <= 5; ++ix)
            printf("%d ", cnt[ix]);
        printf("\n");*/
	}
	for(int ix = 0; ix != m; ++ix)
		printf("%d\n", ans[ix]);
	return 0;
}
