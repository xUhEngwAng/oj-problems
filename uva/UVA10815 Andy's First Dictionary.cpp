#include <string>
#include <iostream>
#include <set>
using namespace std;

/*
 * 本来看起来就是stl水题，没想到ac还颇费了一番周折。
 * 这个题主要是存在以下的问题：
 * 
 * 1. 一开始的循环写的是 while(isLetter(str[ix])) ++ix; 会导致
 *    索引出界。
 * 2. 对题目的理解不准确，一开始的方案只是[掐头去尾]，把可能出现
 *    在首尾的非字母字符剔除了，但是这些字符还可能出现在中间啊，
 *    比如 Alice's, Mr.Laurance 这种。
 * 3. 把长度为零的字符串也添加到了 dict 当中。
 * 
 * 然后看刘汝佳的题解，发现我定义的 isLetter 还有tolower 都是有现
 * 成函数的(isalpha)，对这些库函数不够熟悉。
 * 此题的收获是，不要对题目的输入进行假设，比如这里的输入未必一定要
 * 是英语单词啊，严格按照题干提供的信息来编码，即单词的定义是连续的
 * 英文字母组成的串。
 */

inline
bool isLetter(char ch){
	return (ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A');
}

int main(){
	string str;
	set<string> dict;
	int begin, len, m, ix;
	while(cin >> str){
		m = str.length();
		begin = 0, len = 0, ix = 0;
		while(ix < m){
			while(ix < m && !isLetter(str[ix])) ++ix;
			begin = ix;
			while(ix < m && isLetter(str[ix])){
				if(str[ix] <= 'Z') 
					str[ix] = str[ix] - 'A' + 'a';
				++ix;
			}
			len = ix - begin;
			if(len) dict.insert(str.substr(begin, len));
		}
	}
	for(string s : dict){
		cout << s << endl;
	}
}
