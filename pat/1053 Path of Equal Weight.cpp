#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct node{
	int weight;
	vector<int> children;
};

vector<node> tree;
vector<vector<int>> res;
int N, M, S;

bool cmp(int left, int right){
	int ix = 0;
	while(res[left][ix] == res[right][ix]) ++ix;
	return res[left][ix] > res[right][ix];
}

void dfs(int root, int sum, vector<int> &seq){
	sum += tree[root].weight;
	seq.push_back(tree[root].weight);
	if(tree[root].children.empty()){
		if(sum == S)
			res.push_back(seq);
		goto ret;
	}else
	if(sum >= S) goto ret;

	for(int e : tree[root].children)
		dfs(e, sum, seq);
	ret:
	sum -= tree[root].weight;
	seq.pop_back();
}

int main(){
	int num, curr, child;
	scanf("%d %d %d", &N, &M, &S);
	tree = vector<node>(N);
	for(int ix = 0; ix != N; ++ix)
		scanf("%d", &tree[ix].weight);
	for(int ix = 0; ix != M; ++ix){
		scanf("%d %d", &curr, &num);
		while(num--){
			scanf("%d", &child);
			tree[curr].children.push_back(child);
		}
	}

	vector<int> seq, order;
	dfs(0, 0, seq);
	for(int ix = 0; ix != res.size(); ++ix)
		order.push_back(ix);
	sort(order.begin(), order.end(), cmp);
	for(int e : order){
		printf("%d", res[e][0]);
		for(int ix = 1; ix != res[e].size(); ++ix)
			printf(" %d", res[e][ix]);
		printf("\n");
	}
}
