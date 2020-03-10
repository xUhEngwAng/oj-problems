#include <cstdio>
#include <vector>
#include <stack>
#include <map>
using namespace std;

/*
 * 这个题我感觉不难啊，但是我写了一个多小时，就总感觉哪里
 * 怪怪的。紫书上面说此题细节比较多，也许是这样吧......
 *
 * 我的算法和紫书也差不多，也是递归地从根节点开始逐渐往下
 * 遍历，我是用一个 map 来存储结果，它是用一个大数组来存
 * 结果（个人感觉不太严谨）。紫书比我厉害的地方在于，它又
 * 没有保存二叉树，边读入就边在计算最后的结果了，我还引入
 * 一个栈来读入数据......
 */

struct node{
	int value;
	node* left;
	node* right;
};

map<int, int> res;
map<int, int>::iterator it;

void countLeaves(node *root, int pos){
	res[pos] += root->value;
	if(root->left->value != -1)
		countLeaves(root->left, pos - 1);
	if(root->right->value != -1)
		countLeaves(root->right, pos + 1);
}

int main(){
	int value, rnd = 1, cnt;
	node tmp, *curr, *root = new node;
	stack<node*> s;
	while(true){
		s.push(root);
		while(!s.empty()){
			curr = s.top();
			s.pop();
			scanf("%d", &value);
			curr->value = value;
			if(value != -1){
				curr->right = new node;
				curr->left  = new node;
				s.push(curr->right);
				s.push(curr->left);
			}
		}
		if(root->value == -1) break;
		printf("Case %d:\n", rnd++);
		res.clear();
		countLeaves(root, 0);
		it = res.begin();
		printf("%d", it->second);
		for(++it; it != res.end(); ++it)
			printf(" %d", it->second);
		printf("\n\n");
	}
	return 0;
}
