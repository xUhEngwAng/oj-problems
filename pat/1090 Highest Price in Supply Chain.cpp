#include <vector>
#include <queue>
#include <cstdio>
#include <cmath>
#include <cstdlib>
using namespace std;

struct node{
	int depth = 0;
	vector<int> children;
};

node* tree;

int main(){
	int N, curr, root;
	double P, rate;
	scanf("%d %lf %lf", &N, &P, &rate);
	tree = new node[N];

	for(int ix = 0; ix != N; ++ix){
		scanf("%d", &curr);
		if(curr == -1) root = ix;
		else tree[curr].children.push_back(ix);
	}

	queue<int> q;
	q.push(root);
	int maxDepth = 0, count = 0;
	while(!q.empty()){
		curr = q.front();
		q.pop();
		for(int e : tree[curr].children){
			q.push(e);
			tree[e].depth = tree[curr].depth + 1;
		}
		if(tree[curr].children.empty()){
			if(tree[curr].depth > maxDepth){
				maxDepth = tree[curr].depth;
				count = 1;
			}else
			if(tree[curr].depth == maxDepth)
				++count;
		}
	}
	printf("%.2f %d", P * pow(1 + rate / 100, maxDepth), count);
	return 0;
}
