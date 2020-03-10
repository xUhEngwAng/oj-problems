#include <cstdio>
#include <stack>
#include <string>
#include <iostream>
using namespace std;

/*
 * 此题不就是一个表达式求值吗，可惜我做的太复杂了，甚至用了
 * 递归来对表达式进行解析。紫书上面的简单算法本来我也是想到
 * 了，可惜还是读题不清楚。
 *
 * 简单算法如下，只引入一个操作数栈，来存储所有的矩阵。每遇到
 * 一个右括号，就从中弹出两个矩阵进行乘运算，并将结果压栈。最
 * 后栈中的矩阵就是运算的结果。
 *
 * 我的问题是，我认为有可能出现类似 (A) 的情况，实际上题目上
 * 已经给出了表达式的正则表达式定义：
 *
 * Expression = Matrix | "(" Expression Expression ")"
 *
 * 就是说括号里面至少有两个子表达式，并且复合表达式一定被括号
 * 包裹的。所以还是吃了对正则表达式不熟练的亏啊。
 */

struct Matrix{
	int row;
	int col;
};

Matrix arr[26];

Matrix parse(string expr, int &cnt){
	Matrix left, right;
	int num = 0, ix = 0, len;
	bool flag = true;
	do{
		if(expr[ix] == '(') ++num;
		if(expr[ix] == ')') --num;
		++ix;
	}while(num != 0);
	if(ix == 1) left = arr[expr[0] - 'A'];
	else left = parse(expr.substr(1, ix - 2), cnt);
	//cout << left.row << ' ' << left.col << endl;
	if(left.row == -1){flag = false; goto ret;}
	while(ix < expr.size()){
		if(isalpha(expr[ix])) right = arr[expr[ix++] - 'A'];
		else{
			len = num = 0;
			while(true){
				if(expr[ix + len] == '(') ++num;
				if(expr[ix + len] == ')') --num;
				++len;
				if(num == 0) break;
			}
			//cout << expr.substr(ix + 1, len - 2);
			right = parse(expr.substr(ix + 1, len - 2), cnt);
			ix += len;
		}
		//cout << right.row << ' ' << right.col << endl;
		if(right.row == -1){flag = false; goto ret;}
		if(left.col != right.row){flag = false; goto ret;}
		cnt += left.row * left.col * right.col;
		left.col = right.col;
	}
	ret:
	if(!flag) left.row = -1;
	return left;
}

int main(){
	int n, row, col;
	scanf("%d", &n);
	char ch;
	for(int ix = 0; ix != n; ++ix){
		scanf("\n%c %d %d", &ch, &row, &col);
		arr[ch - 'A'].row = row;
		arr[ch - 'A'].col = col;
	}
	string str;
	Matrix res;
	int cnt;
	while(cin >> str){
		cnt = 0;
		if(str.size() != 1)
			res = parse(str.substr(1, str.size() - 2), cnt);
		if(res.row == -1) printf("error\n");
		else printf("%d\n", cnt);
	}
	return 0;
}
