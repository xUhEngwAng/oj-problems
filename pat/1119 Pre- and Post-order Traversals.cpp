#include <cstdio>
#include <vector>
using namespace std;

struct node{
	int value;
	node *left = nullptr;
	node *right = nullptr;
};

node *root;
bool uniq = true;
vector<int> res;

node* construct(int *pre, int *post, int n){
	node* ret = new node;
	ret->value = pre[0];
	if(n == 1) return ret;

	int leftroot = pre[1];
	int rightroot = post[n - 2];
	if(leftroot == rightroot){
		uniq =false;
		ret->left = construct(pre + 1, post, n - 1);
	}
	else{
		int leftcnt = 0;
		while(pre[leftcnt + 1] != rightroot) ++leftcnt;
		ret->left = construct(pre + 1, post, leftcnt);
		ret->right = construct(pre + leftcnt + 1, post + leftcnt, n - leftcnt - 1);
	}
	return ret;
}

void inorder(node *root){
	if(root->left)
		inorder(root->left);
	res.push_back(root->value);
	if(root->right)
		inorder(root->right);
}

int main(){
	int N;
	scanf("%d", &N);
	int *pre = new int[N];
	int *post = new int[N];
	for(int ix = 0; ix != N; ++ix)
		scanf("%d", pre + ix);
	for(int ix = 0; ix != N; ++ix)
		scanf("%d", post + ix);

	root = construct(pre, post, N);
	inorder(root);

	if(uniq) printf("Yes\n");
	else printf("No\n");
	printf("%d", res[0]);
	for(int ix = 1; ix != res.size(); ++ix)
		printf(" %d", res[ix]);
	printf("\n");
	return 0;
}
