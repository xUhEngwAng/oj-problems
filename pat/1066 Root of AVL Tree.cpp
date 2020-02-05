#include <stack>
#include <cstdio>
#include <cstdlib>
using namespace std;

/*
 * 谁能想到算法题居然考手写 AVL 树呢？然后我是用指针来实现，
 * 用数组来做我是觉得太浪费空间了，题目也没有给关键码的范围。
 * 由于用了指针，代码中就出现了不少奇怪的错误，debug 颇费了
 * 一番时间。
 *
 * 一个主要的问题，是关于指针形参的赋值问题。我的 insert 函数
 * 本来的形式是
 *
 * void insert(node *root, int key)
 *
 * 我期望这个函数可以在 root = nullptr 时给 root 动态分配
 * 空间，然而这是做不到的，因为分配的空间只是给形参的，不是
 * 给实参 root 的，所以后来我才把 root 调整为指针的引用了。
 * 实际上，在函数参数传递这一块，指针和普通的变量没有差别，
 * 函数中的修改都无法反映到实参当中，只有使用引用或者指针（
 * 的指针）才能实现；区别在于，使用指针作为参数，虽然无法改
 * 变指针本身，却可以改变被指向的变量的值。
 *
 * 有一说一，邓公的**3+4重构**确实厉害。
 */

#define MAX(X, Y) (X>Y? X: Y)
#define HEIGHT(X) (X? X->height: -1)

struct node{
	node *left;
	node *right;
	int key;
	int height;

	node() = default;
	node(int key): left(nullptr), right(nullptr), key(key), height(0){}
};

bool balanced(node *curr){
	int leftHeight = (curr->left? curr->left->height: -1);
	int rightHeight = (curr->right? curr->right->height: -1);
	int diff = leftHeight - rightHeight;
	if(diff <= 1 && diff >= -1) return true;
	return false;
}

void updateHeight(node *curr){
	curr->height = MAX(HEIGHT(curr->left), HEIGHT(curr->right)) + 1;
}

node* connect34(node *g, node *p, node *x){
	node *left, *root, *right;
	node *T1, *T2, *T3, *T4;
	if(g->key > p->key){
		right = g;
		if(x->key > p->key){
			root = x; left = p;
			T1 = left->left; T2 = root->left;
			T3 = root->right; T4 = right->right;
		}
		else{
			root = p; left = x;
			T1 = left->left; T2 = left->right;
			T3 = root->right; T4 = right->right;
		}
	}
	else{
		if(p->key > x->key){
			right = p; root = x; left = g;
			T1 = left->left; T2 = root->left;
			T3 = root->right; T4 = right->right;
		}
		else{
			right = x; root = p; left = g;
			T1 = left->left; T2 = root->left;
			T3 = right->left; T4 = right -> right;
		}
	}

	root->left = left; root->right = right;
	left->left = T1; left->right = T2;
	right->left = T3; right->right = T4;
	updateHeight(left);
	updateHeight(right);
	updateHeight(root);
	return root;
}

void insert(node* &root, int key){
    if(root == nullptr){
        root = new node(key);
        return;
    }
	stack<node*> s;
	node* curr = root;
	while(curr){
		s.push(curr);
		if(key < curr->key)
			curr = curr->left;
		else curr = curr->right;
	}
	curr = new node(key);
	if(s.top()->key < key)
        s.top()->right = curr;
    else s.top()->left = curr;

	int prevHeight;
	node *p, *x, *g;
	while(!s.empty()){
		curr = s.top();
		s.pop();
		prevHeight = curr->height;
		updateHeight(curr);
		if(prevHeight == curr->height) break;
		if(!balanced(curr)){
			p = (HEIGHT(curr->left) > HEIGHT(curr->right)?
				curr->left: curr->right);
			x = (HEIGHT(p->left) > HEIGHT(p->right)?
				p->left: p->right);
			g = connect34(curr, p, x);
			if(s.empty())
                root = g;
            else{
                if(s.top()->left == curr)
                    s.top()->left = g;
                else s.top()->right = g;
            }
			break;
		}
	}
}

int main(){
	int N, curr;
	scanf("%d", &N);
	node *root = nullptr;
	for(int ix = 0; ix != N; ++ix){
		scanf("%d", &curr);
		insert(root, curr);
	}
	printf("%d\n", root->key);
	return 0;
}
