#include <stdio.h>
#include <map>
#include <vector>
#include <queue>
using namespace std;
struct node{
	int left; 
	int right;
};
vector<int> postOrder, inOrder;
map<int,node> tree;
void find_child(vector<int> &inorder, int root) {
	node currnode;
	if(inorder.size() == 1){
		currnode.left = currnode.right = -1;
		tree[root] = currnode;
		return;
	}
	vector<int> left, right;
	auto pos = find(inorder.begin(), inorder.end(), root);
	left.assign(inorder.begin(), pos);
	right.assign(pos + 1, inorder.end());
	int leftchild, rightchild, leftcount = 0, rightcount = 0;
	if (left.empty()) leftchild = -1;
	else if (left.size() == 1) leftchild = left.front();
	else {
		for (auto It = postOrder.begin(); It != postOrder.end(); It++) {
			if (find(left.cbegin(), left.cend(), *It) != left.cend()) ++leftcount;
			if(leftcount == left.size()){
				leftchild = *It;
				break;
			}
		}
	}
	if (right.empty()) rightchild = -1;
	else if (right.size() == 1) rightchild = right.front();
	else {
		for (auto It = postOrder.begin(); It != postOrder.end(); It++) {
			if (find(right.cbegin(), right.cend(), *It) != right.cend()) ++rightcount;
			if (rightcount == right.size()) {
				rightchild = *It;
				break;
			}
		}
	}
	currnode.left = leftchild;
	currnode.right = rightchild;
	tree[root] = currnode;
	if(!left.empty()) find_child(left, leftchild);
	if(!right.empty()) find_child(right, rightchild);
}
int main(){
	int N, value, root;
	scanf("%d", &N);
	for (int ix = 0; ix != N; ix++) {
		scanf("%d", &value);
		postOrder.push_back(value);
	}
	for (int ix = 0; ix != N; ix++){
		scanf("%d", &value);
		inOrder.push_back(value);
	}
	root = postOrder.back();
	find_child(inOrder, root);
	queue<int> intque;
	intque.push(root);
	int currnode;
	while(!intque.empty()){
		currnode = intque.front();
		intque.pop();
		if (currnode == root) printf("%d", currnode);
		else printf(" %d", currnode);
		if (tree[currnode].left != -1) intque.push(tree[currnode].left);
		if (tree[currnode].right != -1) intque.push(tree[currnode].right);
	}
	system("pause");
	return 0;
}
