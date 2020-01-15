#include <string>
#include <algorithm>
#include <iostream>
#include <set>
using namespace std;

/*
 * 这个题简单归简单，中间还是遇到了一些问题，主要还是一些
 * 函数接口不熟悉。
 * 1. string.find 返回值是 string::size_type，大约是无
 *    符号整型；而 find 函数返回的是迭代器。
 * 2. tolower, toupper 并不会改变传入的字符，而是返回其
 *    小写/大写形式。
 * 我这里是用了一个 set 来保证不重复输出，看《算法笔记》使用
 * 的是散列，感觉更加高效。但是对于散列的使用（bitset, 
 * unordered_set, unordered_map）我还不会......
 */

int main(){
	string origin, printout;
	cin >> origin >> printout;
	set<char> s;
	char ch;
	for(int pos = 0; ;++pos){
		pos = origin.find_first_not_of(printout, pos);
		if(pos == -1) break;

		ch = origin[pos];
		if(isalpha(ch)) ch = toupper(ch);
		if(s.find(ch) == s.end()) s.insert(ch);
		else continue;

		cout << ch;
	}
	return 0;
}
