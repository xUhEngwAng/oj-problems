#include <iostream>
#include <string>
using namespace std;

#define INF (0x7fffffff)

struct node{
	int left = -1;
	int right = -1;
};

node tree[10000];
int inorder[10000], postorder[10000];
int minpath, minleaf;

int construct(int *inorder, int *postorder, int n){
	if(n == 0) return -1;
	int root = postorder[n - 1];
	int pos = 0;
	while(inorder[pos] != root) ++pos;
	tree[root].left  = construct(inorder, postorder, pos);
	tree[root].right = construct(inorder + pos + 1, postorder + pos, n - pos - 1);
	return root;
}

void dfs(int origin, int pathvalue){
	pathvalue += origin;
	if(pathvalue > minpath) return;
	if(tree[origin].left == -1 && tree[origin].right == -1){
		if(pathvalue < minpath || origin < minleaf){
			minpath = pathvalue;
			minleaf = origin;
		}
	}
	if(tree[origin].left != -1)
		dfs(tree[origin].left, pathvalue);
	if(tree[origin].right != -1)
		dfs(tree[origin].right, pathvalue);
}

int main(){
	int cnt, start, next, root;
	string str;
	while(true){
		getline(cin, str);
		if(!cin) break;
		cnt = start = 0;
		while(true){
			next = str.find(' ', start);
			if(next == -1) break;
			inorder[cnt++] = stoi(str.substr(start, next - start));
			start = next + 1;
		}
		inorder[cnt++] = stoi(str.substr(start));
		for(int ix = 0; ix != cnt; ++ix)
			cin >> postorder[ix];
		root = construct(inorder, postorder, cnt);
		minpath = minleaf = INF;
		dfs(root, 0);
		cout << minleaf << endl;
        cin.ignore();
	}
	return 0;
}
