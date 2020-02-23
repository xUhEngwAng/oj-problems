#include <deque>
#include <iostream>
#include <string>
using namespace std;

/*
 * 这个题我的方法显得不太聪明的样子......为了遍历环形
 * 序列从任一个位置开始的情况，我使用了一个 deque 来
 * 加快前端字符的删除以及后端字符的插入。然而我看紫书
 * 的题解根本就没有进行真正的删除和插入操作，只是不断
 * 调整起始位置的索引，利用 (p + i) % n 就可以进行
 * 环形的访问了。
 */

bool lt(const deque<char>& left, const deque<char>& right){
	bool res;
	for(int ix = 0; ix != left.size(); ++ix){
		if(left[ix] < right[ix]) return true;
		if(left[ix] > right[ix]) return false;
	}
	return false;
}

int main(){
	int N;
	cin >> N;
	char ch;
	deque<char> q, min;
	string input;
	while(N--){
		q.clear();
		cin >> input;
		for(char ch : input)
			q.push_back(ch);
		min.assign(q.begin(), q.end());
		for(int ix = 1; ix != q.size(); ++ix){
			ch = q.front();
			q.pop_front();
			q.push_back(ch);
			if(lt(q, min))
				min.assign(q.begin(), q.end());
		}
		for(char ch : min)
			cout << ch;
		cout << endl;
	}
	return 0;
}
