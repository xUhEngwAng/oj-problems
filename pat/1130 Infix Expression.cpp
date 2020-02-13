#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct node{
	string data;
	int left;
	int right;

	node() = default;
};

vector<node> tree;

string inorder(int root){
	if(tree[root].left == -1 && tree[root].right == -1)
		return tree[root].data;
	string res = "(";
	if(tree[root].left != -1)
		res += inorder(tree[root].left);
	res += tree[root].data;
	if(tree[root].right != -1)
		res += inorder(tree[root].right);
	res += ")";
	return res;
}

int main(){
	int N, lc, rc;
	string str;
	cin >> N;
	tree = vector<node>(N + 1);
	vector<bool> isroot(N + 1, true);
	for(int ix = 1; ix <= N; ++ix){
		cin >> tree[ix].data >> tree[ix].left >> tree[ix].right;
		if(tree[ix].left != -1) isroot[tree[ix].left] = false;
		if(tree[ix].right != -1) isroot[tree[ix].right] = false;
	}
	int root = 1;
	while(!isroot[root]) ++root;
	string res = inorder(root);
	if(res[0] != '(') cout << res << endl;
	else{
        res.pop_back();
        cout << res.substr(1) << endl;
	}
	return 0;
}
