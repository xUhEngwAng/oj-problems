#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

/*
 * 就是一个朴素的求斐波拉契数列第n项以及高精度加法的问题。本来
 * 想用矩阵快速幂来做的，太懒了不太想写......看到一个大佬的
 * 题解用了高精度 + 矩阵快速幂 + fft加速大数乘法，也太强了！
 */

string steps[5001];

string add(const string &left, const string &right){
	int one, two, curr, carry = 0;
	string ret;
	for(int ix = left.size() - 1, jx = right.size() - 1; ix >= 0 || jx >= 0; --ix, --jx){
		one = (ix >= 0? left[ix] - '0': 0);
		two = (jx >= 0? right[jx] - '0': 0);
		curr = one + two + carry;
		carry = curr / 10;
		curr = curr - 10 * carry;
		ret.push_back(curr + '0');
	}
	if(carry) ret.push_back('1');
	reverse(ret.begin(), ret.end());
	return ret;
}

int main(){
	int n;
	cin >> n;
	steps[0] = "1";
	steps[1] = "1";
	for(int ix = 2; ix <= n; ++ix)
		steps[ix] = add(steps[ix - 1], steps[ix - 2]);
    if(n == 0) cout << 0 << endl;
	else cout << steps[n] << endl;
	return 0;
}
