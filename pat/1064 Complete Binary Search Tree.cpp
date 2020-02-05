#include <cstdio>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;

/*
 * 我本来还以为我的方法挺简单挺巧妙的，没想到《算法笔记》的题解
 * 比我还要巧妙。
 *
 * 这个题其实就是清华考研数据结构的最后一个大题啊，所以我就按
 * 那个时候的方法直接写了，简单说来，对于节点数量为 N 的完全
 * 二叉树，都可以通过一定的数学表达式找出它的根节点的位置，体
 * 现在我实现的 getRoot 函数当中。从而就可以递归地构造出原来的
 * 完全二叉树了。
 *
 * 参考题解是首先引入一个数组来表示完全二叉树，即下标为 ix 的
 * 节点，其左右孩子节点的下标分别是 2 * ix 和 2 * ix + 1。该
 * 数组一开始所有节点的关键码都是空的。对这棵完全二叉树做中序
 * 遍历，则遍历的结果就是关键码的升序排序序列，因此可以在遍历
 * 过程中为关键码依次赋值。
 *
 * 完全二叉树构造完成后，直接输出该数组，就是层次遍历序列了。
 * （这也太巧妙了吧！
 */

struct node{
	int left = -1;
	int right = -1;
};

node tree[2001];

int getRoot(int num){
	int h = log(num) / log(2), root;
	int size = (1 << (h - 1)); //2^(h - 1)
	if(num <= 3 * size - 1)
		root = num - size;
	else
		root = size * 2 - 1;
	return root;
}

int constructCBT(int* keys, int N){
	if(N == 0) return -1;
	if(N == 1) return keys[0];
	int rootIdx = getRoot(N);
	int root = keys[rootIdx];
	tree[root].left = constructCBT(keys, rootIdx);
	tree[root].right = constructCBT(keys + rootIdx + 1, N - rootIdx - 1);
	return root;
}

int main(){
	int N, curr, root;
	scanf("%d", &N);
	int *keys = new int[N];
	for(int ix = 0; ix != N; ++ix)
		scanf("%d", keys + ix);
	sort(keys, keys + N);
	root = constructCBT(keys, N);

	queue<int> q;
	vector<int> seq;
	q.push(root);

	while(!q.empty()){
		curr = q.front();
		q.pop();
		seq.push_back(curr);
		if(tree[curr].left != -1)
			q.push(tree[curr].left);
		if(tree[curr].right != -1)
			q.push(tree[curr].right);
	}

	printf("%d", seq[0]);
	for(int ix = 1; ix != seq.size(); ++ix)
		printf(" %d", seq[ix]);
	return 0;
}
