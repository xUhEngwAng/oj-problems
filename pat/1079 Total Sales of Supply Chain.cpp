#include <queue>
#include <vector>
#include <cstdio>
#include <cmath>
using namespace std;

/*
 * 又是直接通过，好没意思啊（误
 * 
 * 这个题也有一个细节需要注意，对于 double 型数据的输入和
 * 输出，scanf 中需要使用 %lf 标志符，而在 printf 中使用
 * %f 就可以了。
 */

struct node{
	int depth = 0;
	double amount;
	vector<int> children;
};

node *tree;

int main(){
	int N, count, curr;
	double P, rate, amount;
	scanf("%d %lf %lf", &N, &P, &rate);
	tree = new node[N];

	for(int ix = 0; ix != N; ++ix){
		scanf("%d", &count);
		if(count == 0){
			scanf("%lf", &amount);
			tree[ix].amount = amount;
		}
		else{
			tree[ix].children.reserve(count);
			while(count--){
				scanf("%d", &curr);
				tree[ix].children.push_back(curr);
			}
		}
	}

	queue<int> q;
	q.push(0);
	tree[0].depth = 0;
	double res = 0;
	while(!q.empty()){
		curr = q.front();
		q.pop();
		for(int child : tree[curr].children){
			q.push(child);
			tree[child].depth = tree[curr].depth + 1;
		}
		if(tree[curr].children.empty())
			res += tree[curr].amount * P *
		           pow(1 + rate/100, tree[curr].depth);
	}
	printf("%.1f\n", res);
	return 0;
}
