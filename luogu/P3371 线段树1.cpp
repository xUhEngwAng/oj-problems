#include <cstdio>
#define MAXN (1 << 18)

struct node{
	long long value;
	long long lazy_tag = 0;
	int left, right;
}tree[MAXN];

long long arr[100001];

void build(int pos, int l, int r){
	tree[pos].left = l;
	tree[pos].right = r;
	if(l == r){
		tree[pos].value = arr[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(pos << 1, l, mid);
	build(pos << 1 | 1, mid + 1, r);
	tree[pos].value = tree[pos << 1].value + tree[pos << 1 | 1].value;
}

void pushdown(int pos){
	int lc = pos << 1, rc = pos << 1 | 1;
	tree[lc].value += tree[pos].lazy_tag * (tree[lc].right - tree[lc].left + 1);
	tree[lc].lazy_tag += tree[pos].lazy_tag;
	tree[rc].value += tree[pos].lazy_tag * (tree[rc].right - tree[rc].left + 1);
	tree[rc].lazy_tag += tree[pos].lazy_tag;
	tree[pos].lazy_tag = 0;
}

long long query(int pos, int l, int r){
	if(tree[pos].left >= l && tree[pos].right <= r)
		return tree[pos].value;
	if(tree[pos].lazy_tag)
		pushdown(pos);
	long long ret = 0;
	if(tree[pos << 1].right >= l)
		ret += query(pos << 1, l, r);
	if(tree[pos << 1 | 1].left <= r)
		ret += query(pos << 1 | 1, l, r);
	return ret;
}

void add(int pos, long long value, int l, int r){
	if(tree[pos].left >= l && tree[pos].right <= r){
		tree[pos].value += value * (tree[pos].right - tree[pos].left + 1);
		tree[pos].lazy_tag += value;
		return;
	}
	if(tree[pos].lazy_tag)
		pushdown(pos);
	if(tree[pos << 1].right >= l)
		add(pos << 1, value, l, r);
	if(tree[pos << 1 | 1].left <= r)
		add(pos << 1 | 1, value, l, r);
	tree[pos].value = tree[pos << 1].value + tree[pos << 1 | 1].value;
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	for(int ix = 1; ix <= n; ++ix)
		scanf("%d", arr + ix);
	build(1, 1, n);
	int cmd, x, y;
	long long value;
	for(int ix = 0; ix != m; ++ix){
		scanf("%d %d %d", &cmd, &x, &y);
		if(cmd == 1){
			scanf("%lld", &value);
			add(1, value, x, y);
		}
		else{
			value = query(1, x, y);
			printf("%lld\n", value);
		}
	}
	return 0;
}
