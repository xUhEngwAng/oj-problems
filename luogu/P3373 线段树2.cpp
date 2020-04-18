#include <cstdio>
#define MAXN (1 << 18)

struct node{
	long long value, left, right;
	int add_tag = 0, mlt_tag = 1;
}tree[MAXN];

int arr[100001], p;

void build(int pos, int l, int r){
	tree[pos].left = l;
	tree[pos].right = r;
	if(l == r){
		tree[pos].value = arr[l] % p;
		return;
	}
	int mid = (l + r) >> 1;
	build(pos << 1, l, mid);
	build(pos << 1 | 1, mid + 1, r);
	tree[pos].value = tree[pos << 1].value + tree[pos << 1 | 1].value;
	tree[pos].value = tree[pos].value % p;
}

void pushdown(int pos){
	int lc = pos << 1, rc = pos << 1 | 1;
	tree[lc].value = (tree[lc].value * tree[pos].mlt_tag + (tree[lc].right - tree[lc].left + 1) * tree[pos].add_tag) % p;
	tree[rc].value = (tree[rc].value * tree[pos].mlt_tag + (tree[rc].right - tree[rc].left + 1) * tree[pos].add_tag) % p;
	tree[lc].mlt_tag = (tree[lc].mlt_tag * tree[pos].mlt_tag) % p;
	tree[rc].mlt_tag = (tree[rc].mlt_tag * tree[pos].mlt_tag) % p;
	tree[lc].add_tag = (tree[lc].add_tag * tree[pos].mlt_tag + tree[pos].add_tag) % p;
	tree[rc].add_tag = (tree[rc].add_tag * tree[pos].mlt_tag + tree[pos].add_tag) % p;
	tree[pos].add_tag = 0;
	tree[pos].mlt_tag = 1;
}

long long query(int pos, int l, int r){
	if(tree[pos].left >= l && tree[pos].right <= r)
		return tree[pos].value;
	if(tree[pos].add_tag || tree[pos].mlt_tag != 1)
		pushdown(pos);
	long long ret = 0;
	if(tree[pos << 1].right >= l)
		ret += query(pos << 1, l, r);
	if(tree[pos << 1 | 1].left <= r)
		ret += query(pos << 1 | 1, l, r);
	return ret % p;
}

void add(int pos, long long value, int l, int r){
	if(tree[pos].left >= l && tree[pos].right <= r){
		tree[pos].add_tag = (tree[pos].add_tag + value) % p;
		tree[pos].value += value * (tree[pos].right - tree[pos].left + 1);
		tree[pos].value = tree[pos].value % p;
		return;
	}
	if(tree[pos].add_tag || tree[pos].mlt_tag != 1)
		pushdown(pos);
	if(tree[pos << 1].right >= l)
		add(pos << 1, value, l, r);
	if(tree[pos << 1 | 1].left <= r)
		add(pos << 1 | 1, value, l, r);
	tree[pos].value = tree[pos << 1].value + tree[pos << 1 | 1].value;
	tree[pos].value = tree[pos].value % p;
}

void mlt(int pos, long long value, int l, int r){
	if(tree[pos].left >= l && tree[pos].right <= r){
		tree[pos].mlt_tag = (tree[pos].mlt_tag * value) % p;
		tree[pos].add_tag = (tree[pos].add_tag * value) % p;
		tree[pos].value = (tree[pos].value * value) % p;
		return;
	}
	if(tree[pos].add_tag || tree[pos].mlt_tag != 1)
		pushdown(pos);
	if(tree[pos << 1].right >= l)
		mlt(pos << 1, value, l, r);
	if(tree[pos << 1 | 1].left <= r)
		mlt(pos << 1 | 1, value, l, r);
	tree[pos].value = tree[pos << 1].value + tree[pos << 1 | 1].value;
	tree[pos].value = tree[pos].value % p;
}

int main(){
	int m, n;
	scanf("%d %d %d", &n, &m, &p);
	for(int ix = 1; ix <= n; ++ix)
		scanf("%d", arr + ix);
	build(1, 1, n);
	int cmd, x, y;
	long long value;
	for(int ix = 0; ix != m; ++ix){
		scanf("%d %d %d", &cmd, &x, &y);
		if(cmd == 3){
			value = query(1, x, y);
			printf("%lld\n", value);
			value = 0;
			for(int ix = x; ix <= y; ++ix)
                value += arr[ix];
            value = value % p;
            printf("%lld\n", value);
		}else{
			scanf("%lld", &value);
			if(cmd == 1){
                mlt(1, value, x, y);
                for(int ix = x; ix <= y; ++ix)
                    arr[ix] = arr[ix] * value;
			}
			else{
                add(1, value, x, y);
                for(int ix = x; ix <= y; ++ix)
                    arr[ix] = arr[ix] + value;
			}
			for(int ix = 1; ix <= n; ++ix)
                printf("%lld ", arr[ix]);
            printf("\n");
		}
	}
	return 0;
}
