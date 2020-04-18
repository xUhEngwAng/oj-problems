#include <cstdio>
#define MAXN      (1 << 20)
#define INF       (0x7fffffff)
#define MAX(X, Y) ((X) > (Y)? (X): (Y))

struct node{
	int max, hist_max;
	int add_tag = 0, min_tag = INF;
}t[MAXN];

int arr[500001];

void build(int pos, int l, int r){
	if(l == r){
		t[pos].max = arr[l];
		t[pos].hist_max = t[pos].max;
		return;
	}
	int mid = (l + r) >> 1;
	build(pos << 1, l, mid);
	build(pos << 1 | 1, mid + 1, r);
	t[pos].max = MAX(t[pos << 1].max, t[pos << 1 | 1].max);
	t[pos].hist_max = t[pos].max;
}

void pushdown(int pos, int l, int r){
	int mid = (l + r) >> 1;
	t[pos << 1].max += t[pos].add_tag;
	
}

void add(int pos, int k, int left, int right, int l, int r){
	if(l <= left && right <= r){
		t[pos].max += k;
		if(t[pos].max > t[pos].hist_max) t[pos].hist_max = t[pos].max;
		t[pos].add_tag += k;
		if(t[pos].min_tag != INF)  t[pos].min_tag += k;
		return;
	}
	if(t[pos].add_tag || t[pos].min_tag != INF)
		pushdown(pos, left, right);
	int mid = (left + right) >> 1;
	if(mid >= l) add(pos << 1, k, left, mid, l, r);
	if(mid + 1 <= r) add(pos << 1 | 1, k, mid + 1, right, l, r);
	t[pos].max = MAX(t[pos << 1].max, t[pos << 1 | 1].max);
	if(t[pos].max > t[pos].hist_max)
		t[pos].hist_max = t[pos].max;
}

void min(int pos, int k, int left, int right, int l, int r){
	if(l <= left && right <= r){
		if(t[pos].max > k) t[pos].max = k;
		if(t[pos].min_tag > k) t[pos].min_tag = k;
		return;
	}
	if(t[pos].add_tag || t[pos].min_tag != INF)
		pushdown(pos, left, right);
	int mid = (left + right) >> 1;
	if(mid >= l) min(pos << 1, k, left, mid, l, r);
	if(mid + 1 <= r) min(pos << 1 | 1, k, mid + 1, right, l, r);
	t[pos].max = MAX(t[pos << 1].max, t[pos << 1 | 1].max);
	if(t[pos].max > t[pos].hist_max)
		t[pos].hist_max = t[pos].max;
}

int sum(int pos, int left, int right, int l, int r){
	if(left == right) return t[pos].max;
	if(t[pos].add_tag || t[pos].min_tag != INF)
		pushdown(pos, left, right);
	int ret = 0;
	int mid = (left + right) >> 1;
	if(mid >= l) ret += sum(pos << 1, left, mid, l, r);
	if(mid + 1 <= r) ret += sum(pos << 1 | 1, mid + 1, right, l, r);
	return ret;
}

int max1(int pos, int left, int right, int l, int r){
	if(l <= left && right <= r) return t[pos].max;
	if(t[pos].add_tag || t[pos].min_tag != INF)
		pushdown(pos, left, right);
	int ret1 = -INF, ret2 = -INF;
	int mid = (left + right) >> 1;
	if(mid >= l) ret1 = max1(pos << 1, left, mid, l, r);
	if(mid + 1 <= r) ret2 = max1(pos << 1 | 1, mid + 1, right, l, r);
	return MAX(ret1, ret2);
}

int max2(int pos, int left, int right, int l, int r){
	if(l <= left && right <= r) return t[pos].hist_max;
	if(t[pos].add_tag || t[pos].min_tag != INF)
		pushdown(pos, left, right);
	int ret1 = -INF, ret2 = -INF;
	int mid = (left + right) >> 1;
	if(mid >= l) ret1 = max2(pos << 1, left, mid, l, r);
	if(mid + 1 <= r) ret2 = max2(pos << 1 | 1, mid + 1, right, l, r);
	return MAX(ret1, ret2);
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	for(int ix = 1; ix <= n; ++ix)
		scanf("%d", arr + ix);
	build(1, 1, n);
	int op, l, r, v;
	for(int ix = 0; ix != m; ++ix){
		scanf("%d %d %d", &op, &l, &r);
		if(op <= 2){
			scanf("%d", &v);
			if(op == 1) add(1, v, 1, n, l, r);
			else        min(1, v, 1, n, l, r);
		}
		if(op == 3) v = sum(1, 1, n, l, r);
		else if(op == 4) v = max1(1, 1, n, l, r);
		else        v = max2(1, 1, n, l, r);
		printf("%d\n", v);
	}
	return 0;
}
