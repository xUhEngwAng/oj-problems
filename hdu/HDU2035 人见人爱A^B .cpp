#define VERSION2
#ifdef VERSION1

/*
 * 我着实太蠢太蠢了。掌握了更加强大的方法（高精度快速幂），就
 * 忘了曾经熟练的技巧了。
 *
 * 这个题一开始是手写高精度快速幂来做的，当 m = 10000 时，数字
 * 会大到比较过分，大约有 O(m) 位，此时每一次迭代的乘法运算需要
 * O(m ^ 2) 的时间复杂度，一共要进行 O(log m) 次迭代，整体时间
 * 复杂度为 O(m ^ 2 x log m)。
 *
 * 但是此题其实只要求最后三位数，也就是对 1000 进行模余运算，这
 * 可以通过每次相乘后都进行一次模余来避免数字溢出。就算不用快速幂，
 * 时间复杂度也只有 O(m) 而已。
 */

#include <string>
#include <cstdio>
#include <algorithm>
using namespace std;

string add(const string &left, const string &right){
	string ret;
	int one, two, curr, carry = 0;
	for(int ix = left.size() - 1, jx = right.size() - 1; ix >= 0 || jx >= 0; --ix, --jx){
		one = (ix >= 0? left[ix] - '0': 0);
		two = (jx >= 0? right[jx] - '0': 0);
		curr = one + two + carry;
		if(curr >= 10){
			curr -= 10;
			carry = 1;
		}else carry = 0;
		ret.push_back(curr + '0');
	}
	if(carry) ret.push_back('1');
	reverse(ret.begin(), ret.end());
	return ret;
}

string multiply_onebit(const string &str, int num){
	string ret;
	int curr, carry = 0;
	for(int ix = str.size() - 1; ix >= 0; --ix){
		curr = (str[ix] - '0') * num + carry;
		carry = curr / 10;
		curr  = curr - 10 * carry;
		ret.push_back(curr + '0');
	}
	if(carry) ret.push_back(carry + '0');
	reverse(ret.begin(), ret.end());
	return ret;
}

string multiply(string left, const string &right){
	string ret;
	for(int ix = right.size() - 1; ix >= 0; --ix){
		ret = add(ret, multiply_onebit(left, right[ix] - '0'));
		left.push_back('0');
	}
	return ret;
}

int main(){
	int a, b, m;
	string res, tmp;
	while(scanf("%d %d", &a, &b) == 2){
		if(a == 0 && b == 0) break;
		tmp = to_string(a);
		res = "1";
		while(b){
			if(b & 1)
				res = multiply(res, tmp);
			tmp = multiply(tmp, tmp);
			b = b >> 1;
		}
		m = res.size();
		if(m > 3) a = stoi(res.substr(m - 3));
		else      a = stoi(res);
		printf("%d\n", a);
	}
	return 0;
}

#else

//VERSION2

#include <cstdio>

int main(){
	int a, b, res;
	while(scanf("%d %d", &a, &b) == 2){
		if(a == 0 && b == 0) break;
		res = 1;
		for(int ix = 0; ix != b; ++ix)
			res = res * a % 1000;
		printf("%d\n", res);
	}
	return 0;
}

#endif
