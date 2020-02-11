#include <cstdio>

struct node{
	node *left;
	node *right;
	int value;

	node(int key): value(key), left(nullptr), right(nullptr){}
};

void insert(node* &root, int value){
	if(root == nullptr){
		root = new node(value);
		return;
	}
	node *curr = root, *prev;
	while(curr){
		prev = curr;
		if(value <= curr->value)
			curr = curr->left;
		else curr = curr->right;
	}
	if(value <= prev->value)
		prev->left = new node(value);
	else prev->right = new node(value);
}

int max, submax, n1, n2;
void dfs(node *root, int depth){
	if(depth > submax){
		if(depth > max){
			submax = max;
			max = depth;
			n2 = n1, n1 = 1;
		}
		else
		if(depth == max) n1++;
		else{
			submax = depth;
			n2 = 1;
		}
	}else
	if(depth == submax)
		n2++;
	if(root->left) dfs(root->left, depth + 1);
	if(root->right) dfs(root->right, depth + 1);
}

int main(){
	int N, curr;
	scanf("%d", &N);
	node *root = nullptr;
	for(int ix = 0; ix != N; ++ix){
		scanf("%d", &curr);
		insert(root, curr);
	}
	max = submax = -1, n1 = n2 = 0;
	dfs(root, 0);
	printf("%d + %d = %d\n", n1, n2, n1 + n2);
	return 0;
}
