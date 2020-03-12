#include <string>
#include <iostream>
#include <stack>
using namespace std;

/*
 * 此题的思路还是比较简单的，就分为建树和统计两个过程，我分别
 * 写了一个函数。建树过程就是 dfs 的过程，用一个栈轻松解决。统
 * 计过程使用递归来实现，需要保证每轮递归时，两棵子树的根节点
 * 在同一个层次上。
 *
 * 我看紫书上面的参考答案，直接把 32x32 的像素给画出来了，这
 * 也太暴力了！
 */

struct node{
	int color = 0;
	int one = -1, two = -1, three = -1, four = -1;
};

node first[1365], second[1365];

void build(string str, node *tree){
	int cnt = 1, ix = 0, curr;
	stack<int> s;
	s.push(0);
	while(!s.empty()){
		curr = s.top();
		s.pop();
		if(str[ix] == 'p'){
            tree[curr].color = 0;
			tree[curr].one   = cnt++;
			tree[curr].two   = cnt++;
			tree[curr].three = cnt++;
			tree[curr].four  = cnt++;
			s.push(tree[curr].four);
			s.push(tree[curr].three);
			s.push(tree[curr].two);
			s.push(tree[curr].one);
		}
		else{
        tree[curr].one = -1;
        tree[curr].two = -1;
        tree[curr].three = -1;
        tree[curr].four = -1;
		if(str[ix] == 'f')
            tree[curr].color = 1;
        else
            tree[curr].color = 0;
		}
		++ix;
	}
}

int add(int lroot, int rroot, int weight){
	int res = 0;
	if(lroot == -1 && rroot == -1) return 0;
	if(lroot == -1){
		if(second[rroot].color == 1) return weight;
		res += add(-1, second[rroot].one, weight / 4);
		res += add(-1, second[rroot].two, weight / 4);
		res += add(-1, second[rroot].three, weight / 4);
		res += add(-1, second[rroot].four, weight / 4);
		return res;
	}
	if(rroot == -1){
		if(first[lroot].color == 1) return weight;
		res += add(first[lroot].one, -1, weight / 4);
		res += add(first[lroot].two, -1, weight / 4);
		res += add(first[lroot].three, -1, weight / 4);
		res += add(first[lroot].four, -1, weight / 4);
		return res;
	}
	if(first[lroot].color == 1 || second[rroot].color == 1)
		return weight;
	res += add(first[lroot].one, second[rroot].one, weight / 4);
	res += add(first[lroot].two, second[rroot].two, weight / 4);
	res += add(first[lroot].three, second[rroot].three, weight / 4);
	res += add(first[lroot].four, second[rroot].four, weight / 4);
	return res;
}

int main(){
	int n, res;
	string str;
	cin >> n;
	while(n--){
		cin >> str;
		build(str, first);
		cin >> str;
		build(str, second);
		res = add(0, 0, 1024);
		cout << "There are " << res << " black pixels." << endl;
	}
	return 0;
}
