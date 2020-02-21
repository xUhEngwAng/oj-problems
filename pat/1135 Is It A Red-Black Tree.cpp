#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

enum Color{RED, BLACK};

struct node{
	node *left  = nullptr;
	node *right = nullptr;
	int key;
	Color color;
	node(int value){
		key = abs(value);
		if(value < 0) color = RED;
		else          color = BLACK;
	}
};

node* construct(vector<int>::iterator preIt,
	            vector<int>::iterator inIt, int N){
	if(N == 0) return nullptr;
	node *root = new node(*preIt);
	int leftcnt = 0;
	while(leftcnt < N && *(inIt + leftcnt) != root->key) ++leftcnt;
	root->left = construct(preIt + 1, inIt, leftcnt);
	root->right = construct(preIt + leftcnt + 1, inIt + leftcnt + 1, N - leftcnt - 1);
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
	vector<int> preorder, inorder;
	node *root;
	while(K--){
		scanf("%d", &N);
		preorder.resize(N);
		inorder.resize(N);
		for(int ix = 0; ix != N; ++ix){
			scanf("%d", &curr);
			preorder[ix] = curr;
			inorder[ix]  = abs(curr);
		}
		sort(inorder.begin(), inorder.end());
		root = construct(preorder.begin(), inorder.begin(), N);
		if(root->color == RED)
			printf("No\n");
		else{
			if(dfs(root, depth)) printf("Yes\n");
			else                 printf("No\n");
		}
	}
	return 0;
}
