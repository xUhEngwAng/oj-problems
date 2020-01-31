#include <iostream>
#include <string>
using namespace std;

/*
 * 这个题的逻辑感觉是有一点复杂的，要判断不少特殊情况，比如
 * 数字为零时指数需要输出 0。做的过程我遇到的问题主要还是
 * string 的相关成员函数不够熟练。
 *
 * 1. string.find(ch) 返回的并不是迭代器，而是 ch 在字符串
 *    的 index，如果不存在则返回当前数位下的最大（无符号）整
 *    数。
 * 2. string.erase(int pos) 是移除 pos 及其后面的全部字符，
 *    与 string.erase(it) 只移除一个字符完全不同。实际上，
 *    string.erase(pos, len) 移除 pos 及其后面共 len 个字符。
 */

int main(){
	int N;
	string one, two;
	cin >> N >> one >> two;
	int k1 = one.find('.');
	int k2 = two.find('.');
	if(k1 != -1) one.erase(k1 + one.begin());
	else k1 = one.size();
	if(k2 != -1) two.erase(k2 + two.begin());
	else k2 = two.size();
	//cout << one << ' ' << two << endl;

	int pos = 0,m = one.size(), n = two.size();
	while(pos < m && one[pos] == '0'){
		++pos;
		--k1;
	}
	one = one.substr(pos, N);
	if(one.empty()) k1 = 0;
	while(one.size() < N) one.push_back('0');

	pos = 0;
	while(pos < n && two[pos] == '0'){
		++pos;
		--k2;
	}
	two = two.substr(pos, N);
	if(two.empty()) k2 = 0;
	while(two.size() < N) two.push_back('0');

	if(k1 == k2 && one == two){
		cout << "YES 0." << one << "*10^" << k1 << endl;
	}
	else{
		cout << "NO 0." << one << "*10^" << k1
		     <<   " 0." << two << "*10^" << k2 << endl;
	}
	return 0;
}
