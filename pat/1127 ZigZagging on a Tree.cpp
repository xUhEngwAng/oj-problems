#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

struct node{
	node *left = nullptr;
	node *right = nullptr;
	int key;
	node(int key = -1): key(key){}
};

node *construct(int *inorder, int *postorder, int n){
	if(n == 0) return nullptr;
	node *ret = new node(postorder[n - 1]);
	int leftcnt = 0;
	while(inorder[leftcnt] != postorder[n - 1]) ++leftcnt;
	ret->left  = construct(inorder, postorder, leftcnt);
	ret->right = construct(inorder + leftcnt + 1,
		                   postorder + leftcnt, n - 1 - leftcnt);
	return ret;
}

int main(){
	int N;
	scanf("%d", &N);
	int *inorder = new int[N];
	int *postorder = new int[N];
	for(int ix = 0; ix != N; ++ix)
		scanf("%d", inorder + ix);
	for(int ix = 0; ix != N; ++ix)
		scanf("%d", postorder + ix);
	node *root = construct(inorder, postorder, N), *curr;

	vector<int> seq, currlevel;
	queue<node*> q;
	q.push(root);
	int cnt = 1, nextcnt = 0;
	bool direction = false;
	while(!q.empty()){
		curr = q.front();
		q.pop();
		currlevel.push_back(curr->key);
		if(curr->left){
			nextcnt++;
			q.push(curr->left);
		}
		if(curr->right){
			nextcnt++;
			q.push(curr->right);
		}

		if(--cnt == 0){
			cnt = nextcnt;
			nextcnt = 0;
			if(direction)
				seq.insert(seq.end(), currlevel.begin(), currlevel.end());
			else
				seq.insert(seq.end(), currlevel.rbegin(), currlevel.rend());
            direction = !direction;
			currlevel.clear();
		}
	}
	printf("%d", seq.front());
	for(int ix = 1; ix != seq.size(); ++ix)
		printf(" %d", seq[ix]);
	printf("\n");
	return 0;
}
