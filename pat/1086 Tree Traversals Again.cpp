#include <string>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

/*
 * 这个题我的方法是直接构造出了原本的二叉树，然后递归求后序
 * 遍历即可。我看《算法笔记》的解答，上面说中序遍历的 push 的
 * 次序，其实就是二叉树的先序遍历，而 pop 的次序，也就是二
 * 叉树的中序遍历，因此这个题等价于已知先序和中序遍历序列，
 * 求后序遍历序列。
 *
 * 这种分析方法还挺巧妙的，我完全没有想到这一点。但是我觉得我
 * 的方法好像要更好，写起来也比较简洁。
 */

struct node{
	int left;
	int right;

	node():left(-1), right(-1){}
};

node bintree[31];

void postOrder(int root, vector<int> &seq){
	if(bintree[root].left != -1)
		postOrder(bintree[root].left, seq);
	if(bintree[root].right != -1)
		postOrder(bintree[root].right, seq);
	seq.push_back(root);
}

int main(){
	int N, root, curr, tmp;
	bool rightFlag = false;
	string cmd;
	stack<int> s;

	cin >> N;
	cin >> cmd >> root;

	s.push(root);
	curr = root;
	for(int ix = 1; ix != N * 2; ++ix){
		cin >> cmd;
		if(cmd == "Push"){
			cin >> tmp;
			s.push(tmp);
			if(!rightFlag) bintree[curr].left = tmp;
			else{
				bintree[curr].right = tmp;
				rightFlag = false;
			}
			curr = tmp;
		}
		else{
			curr = s.top();
			s.pop();
			rightFlag = true;
		}
	}

	vector<int> seq;
	postOrder(root, seq);
	cout << seq[0];
	for(int ix = 1; ix != N; ++ix)
		cout << ' ' << seq[ix];
	cout << endl;
	return 0;
}
