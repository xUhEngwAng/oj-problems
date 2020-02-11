#include <vector>
#include <queue>
#include <string>
#include <iostream>
using namespace std;

/*
 * 这个题是我蠢了，一开始有三个测试点无论如何都通不过，我甚至
 * 都怀疑我邓公给出的完全二叉树的定义了：
 * 
 * 对于一棵规模为 N 的二叉树，如果它的层次遍历序列中的前 N/2
 * 个节点都有左子树，前 (N - 1)/2 个节点都有右子树，则该二叉
 * 树是一棵完全二叉树。
 *
 * 最后才发现我是输入写错了，节点的输入信息给的是
 *
 * char lc, rc;
 * scanf("\n%c %c", &lc, &rc);
 *
 * 问题是如果 N 比较大，那 lc, rc 就不能用一个 char 来表示了！
 * 所以改成 string 就没有问题了。这里主要还是受到样例的影响吧。
 */

struct node{
	int left = -1;
	int right = -1;
};

int main(){
	int N, curr;
	cin >> N;
	vector<node> tree(N);
    vector<bool> isRoot(N, true);
	string lc, rc;
	for(int ix = 0; ix != N; ++ix){
		cin >> lc >> rc;
		if(lc[0] != '-'){
			tree[ix].left = stoi(lc);
			isRoot[stoi(lc)] = false;
		}
		if(rc[0] != '-'){
			tree[ix].right = stoi(rc);
			isRoot[stoi(rc)] = false;
		}
	}
	int root = 0;
	while(!isRoot[root]) ++root;

	int leftcnt = N >> 1, rightcnt = (N - 1) >> 1;
	queue<int> q;
	q.push(root);
	bool flag = false;
	while(!q.empty()){
		curr = q.front();
		q.pop();
		if(tree[curr].left == -1 && leftcnt > 0){
            flag = true;
            break;
		}
		if(tree[curr].right == -1 && rightcnt > 0){
            flag = true;
            break;
		}

		if(tree[curr].left != -1){
			leftcnt--;
			q.push(tree[curr].left);
		}
		if(tree[curr].right != -1){
			rightcnt--;
			q.push(tree[curr].right);
		}
	}
    if(!flag) printf("YES %d\n", curr);
    else printf("NO %d\n", root);
	return 0;
}
