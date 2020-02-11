#include <vector>
#include <cstdio>
#include <stack>
#include <queue>
#include <cmath>
using namespace std;

#define HEIGHT(X) (X == nullptr? -1: X->height)
#define ISBALANCED(X) (abs(HEIGHT(X->left) - HEIGHT(X->right)) <= 1)
#define MAX(X, Y) ((X) > (Y)? (X): (Y))

struct node{
	int value;
	int height = 0;
	node *left = nullptr;
	node *right = nullptr;

	node(int value = -1): value(value){}
};

void updateHeight(node *curr){
	curr->height = MAX(HEIGHT(curr->left), HEIGHT(curr->right)) + 1;
}

node* higherChild(node* curr){
	node* ret;
	if(HEIGHT(curr->left) > HEIGHT(curr->right))
		ret = curr->left;
	else
		ret = curr->right;
	return ret;
}

node *connect34(node* g, node* p, node* x){
	node *left, *right, *root;
	node *T1, *T2, *T3, *T4;
	if(p == g->left){
		right = g;
		T4 = g->right;
		if(x == p->left){
			left = x, root = p;
			T1 = x->left, T2 = x->right, T3 = p->right;
		}else{
			left = p, root = x;
			T1 = p->left, T2 = x->left, T3 = x->right;
		}
	}
	else{
		left = g;
		T1 = g->left;
		if(x == p->left){
			root = x, right = p;
			T2 = x->left, T3 = x->right, T4 = p->right;
		}else{
			root = p, right = x;
			T2 = p->left, T3 = x->left, T4 = x->right;
		}
	}
	left->left = T1, left->right = T2;
	right->left = T3, right->right = T4;
	root->left = left, root->right =right;
	updateHeight(left);
	updateHeight(right);
	updateHeight(root);
	return root;
}

void insert(node* &root, int value){
	if(root == nullptr){
		root = new node(value);
		return;
	}
	stack<node*> s;
	node *curr = root;
	while(curr){
		s.push(curr);
		if(value < curr->value) curr = curr->left;
		else                    curr = curr->right;
	}
	curr = s.top();
	if(value < curr->value) curr->left  = new node(value);
	else                    curr->right = new node(value);

	int prevHeight;
	while(!s.empty()){
		curr = s.top();
		s.pop();
		prevHeight = curr->height;
		updateHeight(curr);
		if(prevHeight == curr->height) break;
		if(!ISBALANCED(curr)){
			node *p = higherChild(curr), *x = higherChild(p);
			node *g = connect34(curr, p, x);
			if(s.empty())
				root = g;
			else{
				node* newroot = s.top();
				if(curr == newroot->left)
					newroot->left = g;
				else
					newroot->right = g;
			}
			break;
		}
	}
}

int main(){
	int N, curr;
	scanf("%d",&N);
	node *root = nullptr;
	for(int ix = 0; ix != N; ++ix){
		scanf("%d", &curr);
		insert(root, curr);
	}

	int leftcnt = N >> 1, rightcnt = (N - 1) >> 1;
	bool isComplete = true;
	queue<node*> q;
	node* currnode;
	q.push(root);
	vector<int> seq;
	while(!q.empty()){
		currnode = q.front();
		q.pop();
		seq.push_back(currnode->value);
		if(leftcnt > 0 && !currnode->left)
			isComplete = false;
		if(rightcnt > 0 && !currnode->right)
			isComplete = false;
		if(currnode->left){
			leftcnt--;
			q.push(currnode->left);
		}
		if(currnode->right){
			rightcnt--;
			q.push(currnode->right);
		}
	}
	printf("%d", seq.front());
	for(int ix = 1; ix != seq.size(); ++ix)
		printf(" %d", seq[ix]);
	printf("\n");
	if(isComplete) printf("YES\n");
	else printf("NO\n");
	return 0;
}
