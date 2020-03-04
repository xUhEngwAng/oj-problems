#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
 * 这个题的错我找了好久好久，最终发现非常蹊跷。
 *
 * 此题我的建树算法本来是我最熟悉的，通过先序和中序遍历序列来
 * 构造二叉树，输入给出了先序序列，由于这是一棵二叉搜索树，对
 * 先序序列进行排序即可获得中序序列。但是我这种方法却在建树的
 * 递归中陷入了无限递归，因此报了段错误。
 *
 * 经过了大量的尝试，我最终发现问题在于，在某一递归过程中，在
 * 中序序列中没有找到先序遍历序列的头节点，即当前树的根节点，
 * 这在理论上是不可能的，因此我也是一脸懵逼。
 *
 * 后来又经过了不少摸索，我发现如果搜索树中允许存在关键字相同
 * 的节点，并且这种节点可以同时存在于左右子树当中时，我的建树
 * 代码就会失效，因为此时搜索树的构型并不唯一。
 *
 * 解决方案的话，就是不使用中序遍历序列，而是通过查找先序遍历
 * 中第一个大于根节点的节点，来划分左右子树。这种方案还可以节约
 * 内存，运行速度也更快。
 */

enum Color{RED, BLACK};

struct node{
	node *left = nullptr;
	node *right = nullptr;
	int key;
	Color color;
	node(int value){
		key = abs(value);
		if(value < 0) color = RED;
		else          color = BLACK;
	}
};

node* construct(vector<int>::iterator preIt, int N){
	if(N == 0) return nullptr;
	node *root = new node(*preIt);
	int leftcnt = 0;
	while(leftcnt < N && abs(*(preIt + leftcnt)) <= root->key) ++leftcnt;
	root->left  = construct(preIt + 1, leftcnt - 1);
	root->right = construct(preIt + leftcnt, N - leftcnt);
	return root;
}

bool dfs(node *root, int &bheight){
	bool res;
	int leftheight = 0, rightheight = 0;
	if(root->left){
		if(root->color == RED && root->left->color == RED)
			return false;
		res = dfs(root->left, leftheight);
		if(!res) return false;
	}
	if(root->right){
		if(root->color == RED && root->right->color == RED)
			return false;
		res = dfs(root->right, rightheight);
		if(!res) return false;
	}
	if(leftheight != rightheight)
		return false;
	bheight = leftheight;
	if(root->color == BLACK)
		bheight++;
	return true;
}

int main(){
	int K, N, curr, depth;
	scanf("%d", &K);
	vector<int> preorder;
	node *root;
	while(K--){
		scanf("%d", &N);
		preorder.resize(N);
		for(int ix = 0; ix != N; ++ix){
			scanf("%d", &curr);
			preorder[ix] = curr;
		}
		root = construct(preorder.begin(), N);
		if(root->color == RED)   printf("No\n");
		else
			if(dfs(root, depth)) printf("Yes\n");
			else                 printf("No\n");
	}
	return 0;
}
