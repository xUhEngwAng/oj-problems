#include <string>
#include <vector>
#include <iostream>
using namespace std;

/*
 * 此题主要是需要注意一些细节问题，整体的代码倒是难度不大。
 * 我算法的主体就是一个递归程序，其功能是给定根节点，定位
 * 它的所有子节点，然后将当前子树的打印结果写入 res 当中。
 *
 * 首先是说存在一种空树的情况，应该单独对这种情况进行判断，
 * 打印 () 即可。
 *
 * 此外是说，除了样例的输入方式外，还存在许多不同的情况。比
 * 如在节点所在的行也许对出现 # | ' ' - 这样的字符，应该讲
 * 它们忽略掉。  
 */

vector<string> tree;
string res, key = "- #|";

void findChildren(int row, int col){
	res.push_back(tree[row][col]);
	res.push_back('(');
	int left, right;
	if(row == tree.size() - 1) goto ret;
	if(col < tree[row + 1].size() && tree[row + 1][col] == '|'){
		left = right = col;
		while(left >= 0 && tree[row + 2][left] == '-') 
			--left;
		while(right < tree[row + 2].size() && tree[row + 2][right] == '-') 
			++right;
		for(++left; left < right; ++left)
			if(left < tree[row + 3].size() && 
			  key.find(tree[row + 3][left]) == -1)
				findChildren(row + 3, left);
	}
	ret:
	res.push_back(')');
}

int main(){
	//freopen("1.in", "r", stdin);
	//freopen("1.out", "w", stdout);
	int N, ix;
	cin >> N;
	string str;
	cin.ignore();
	while(N--){
		tree.clear();
		while(true){
			getline(cin, str);
			if(str == "#") break;
			tree.push_back(str);
		}
		ix = 0;
		if(tree.empty()){
			cout << "()" << endl;
			continue;
		}
		while(tree[0][ix] == ' ') ++ix;
		res.clear();
		res.push_back('(');
		findChildren(0, ix);
		res.push_back(')');
		cout << res << endl;
	}
	return 0;
}
