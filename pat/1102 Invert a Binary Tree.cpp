#include <queue>
#include <cstdio>
#include <vector>
#include <string>
using namespace std;

/*
 * 这个题本身是简单的，但是又是 char 的输入问题搞了我好久。
 * 问题还是在于 scanf 的 %c 格式是可以读入换行符的，所以要
 * 手动加入 \n 将上一行的换行符接收。这样，读左右子树的代码
 *
 * scanf("\n%c %c", &bintree[ix].left, &bintree[ix].right);
 *
 * 除此以外，我还犯了一个语言的错误，即使用
 *
 * bool isroot[10] = {true};
 *
 * 来对其进行初始化，希望所有元素都被初始化为 true，但是这种
 * 方法只能初始化第一个元素为 true，其余元素都是 false。
 */

struct node{
	char left;
	char right;
};

node bintree[10];
bool isroot[10];

void inOrder(int root, vector<int> &inorder){
	if(isdigit(bintree[root].right))
		inOrder(bintree[root].right - '0', inorder);
	inorder.push_back(root);
	if(isdigit(bintree[root].left))
		inOrder(bintree[root].left - '0', inorder);
}

int main(){
	int N;
	scanf("%d", &N);
	for(int ix = 0; ix != N; ++ix)
        isroot[ix] = true;
	for(int ix = 0; ix != N; ++ix){
		scanf("\n%c %c", &bintree[ix].left, &bintree[ix].right);
		if(isdigit(bintree[ix].left))
			isroot[bintree[ix].left - '0'] = false;
		if(isdigit(bintree[ix].right))
			isroot[bintree[ix].right - '0'] = false;
	}
	int root = 0;
	while(!isroot[root]) ++root;

	vector<int> levelorder;
	queue<int> q;
	q.push(root);
	int curr;
	while(!q.empty()){
		curr = q.front();
		q.pop();
		levelorder.push_back(curr);
		if(isdigit(bintree[curr].right))
			q.push(bintree[curr].right - '0');
		if(isdigit(bintree[curr].left))
			q.push(bintree[curr].left - '0');
	}

	vector<int> inorder;
	inOrder(root, inorder);

	printf("%d", levelorder[0]);
	for(int ix = 1; ix != N; ++ix)
		printf(" %d", levelorder[ix]);
	printf("\n%d", inorder[0]);
	for(int ix = 1; ix != N; ++ix)
		printf(" %d", inorder[ix]);
	printf("\n");
	return 0;
}
