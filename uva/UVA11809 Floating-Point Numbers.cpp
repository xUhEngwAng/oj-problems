#define VERSION2
#ifdef VERSION1

/*
 * 这个题也是几经辗转，才终于做了出来。这里写了两版程序，其基本
 * 思想都是打表，虽然不打表其实也无所谓，毕竟也才300种可能性。
 * 
 * 一开始的思路比较暴力，我是考虑到首先数字很大，double 肯定是
 * 会被爆的，另一方面精度要求也非常高，十进制小数点后15位，double
 * 也无法表示这么高的精度。因此我就手写了大数和高精度，简单说来
 * 是写了自己的十进制 Float 类，其中用 string 表示尾数，用 int
 * 表示阶码，这样精度和大小都可以表示了。
 *
 * 接下来就是打表的过程，首先需要计算十个可能的尾数，其值为
 * (2 ^ i - 1) / (2 ^ i)，需要用 Float 类来进行表示，所以
 * 需要手写除法运算。然后要计算三十个可能的指数，其值分别是
 * exp(E) = 2 ^ (2 ^ E - 1)，我是通过 exp(E) = 2 * exp(E - 1) ^ 2
 * 来简化运算，这样就要手写 Float 的乘法运算，其中又涉及到大数
 * 乘法和大数加法运算，都需要一一实现。最后将三百种情况乘起来
 * 就可以了，这要用到前面实现的 Float 乘法运算。
 *
 * 然后看了看大佬们的解答，简直不要太简单。题意是说
 * (2^(M + 1) - 1) / (2 ^ (M + 1)) x 2 ^ (2 ^ E - 1) == A x 10 ^ B
 * 我的策略就是直接算出了等式的左右两边，大佬是对两边取对数，
 * 所以 lg(2^(M + 1) - 1) / (2 ^ (M + 1)) + (2 ^ E - 1) x lg2 = lgA + B
 * 这样直接对左边打表就可以了，直接用double就行。
 *
 * 这里还有一个精度的问题，看起来输入的精度特别高，其实此题用
 * 不到这么高的精度，尾数的精度不过是 1/1024，此外还要取对数，
 * 因此直接判断输入与表中元素的差值是否不超过 1e-5 即可。
 */

#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

struct Float{
	string mant;
	int exp;
};

Float table[10][31];
Float exponent[31];
Float mantissa[10];

string add(const string &left, const string &right){
	string ret;
	int carry = 0, one, two, curr;
	for(int ix = left.size() - 1, jx = right.size() - 1; 
		ix >= 0 || jx >= 0; --ix, --jx){
		one = (ix >= 0? left[ix] - '0': 0);
		two = (jx >= 0? right[jx] - '0': 0);
		curr = one + two + carry;
		if(curr >= 10){
			curr -= 10;
			carry = 1;
		}
		else carry = 0;
		ret.push_back(curr + '0');
	}
	if(carry) ret.push_back(carry + '0');
	reverse(ret.begin(), ret.end());
	return ret;
}

string multiply_onebit(const string &left, int right){
	string ret;
	int carry = 0, curr;
	for(int ix = left.size() - 1; ix >= 0; --ix){
		curr = (left[ix] - '0') * right + carry;
		if(curr >= 10){
			carry = curr / 10;
			curr  = curr - 10 * carry;
		}
		else carry = 0;
		ret.push_back(curr + '0');
	}
	if(carry) ret.push_back(carry + '0');
	reverse(ret.begin(), ret.end());
	return ret;
}

string multiply(string left, const string &right){
	string ret, tmp;
	for(int ix = right.size() - 1; ix >= 0; --ix){
		tmp = multiply_onebit(left, right[ix] - '0');
		ret = add(ret, tmp);
		left.push_back('0');
	}
	return ret;
}

Float Float_multiply(const Float &one, const Float &two){
	Float ret;
	ret.mant = multiply(one.mant, two.mant);
	ret.exp  = one.exp + two.exp;
	if(ret.mant.size() == 42) ret.exp++;
	ret.mant = ret.mant.substr(0, 21);
	return ret;
}

Float divide(int up, int down){
	Float ret;
	int res;
	for(int ix = 0; ix != 21; ++ix){
		up = up * 10;
		res = up / down;
		up = up - down * res;
		ret.mant.push_back(res + '0');
	}
	ret.exp = -1;
	return ret;
}

void get_exponent(){
	exponent[1].mant = "2";
	exponent[1].exp  = 0;
	for(int ix = 0; ix != 20; ++ix)
		exponent[1].mant.push_back('0');
	for(int ix = 2; ix <= 30; ++ix){
		exponent[ix] = Float_multiply(exponent[1], Float_multiply(
			           exponent[ix - 1], exponent[ix - 1]));
	}
}

void get_mantissa(){
	int demoninator = 2;
	for(int ix = 0; ix != 10; ++ix){
		mantissa[ix] = divide(demoninator - 1, demoninator);
		demoninator = demoninator << 1;
	}
}

void create_table(){
	for(int ix = 0; ix != 10; ++ix)
		for(int jx = 1; jx <= 30; ++jx)
			table[ix][jx] = Float_multiply(mantissa[ix], exponent[jx]);
}

int main(){
	get_exponent();
	get_mantissa();
	create_table();
	/*
	for(int ix = 0; ix != 10; ++ix)
		cout << mantissa[ix].mant << 'e' << mantissa[ix].exp << endl;
	for(int ix = 1; ix <= 30; ++ix)
		cout << exponent[ix].mant << 'e' << exponent[ix].exp << endl;
	
	for(int ix = 0; ix != 10; ++ix)
		for(int jx = 1; jx <= 30; ++jx)
			cout << table[ix][jx].mant << ' ' << table[ix][jx].exp << endl;
	*/
	string str, currmant;
	int currexp, pos;
	while(true){
		cin >> str;
		if(str[0] == '0') break;
		pos = str.find('e');
		currexp = stoi(str.substr(pos + 1));
		currmant = str.substr(0, pos);
		currmant.erase(1 + currmant.begin());
		for(int ix = 0; ix != 10; ++ix)
			for(int jx = 1; jx <= 30; ++jx){
				if(currexp == table[ix][jx].exp &&
				   currmant.substr(0, 10) == table[ix][jx].mant.substr(0, 10)){
					printf("%d %d\n", ix, jx);
				break;
				}
			}
	}
	return 0;
}

#else

//VERSION2

#include <cmath>
#include <iostream>
#include <string>
using namespace std;

double table[10][31];

void create_table(){
	double power, exp;
	for(int ix = 0; ix != 10; ++ix){
		power = pow(2, ix + 1);
		for(int jx = 1; jx <= 30; ++jx){
			exp = pow(2, jx) - 1;
			table[ix][jx] = log10((double)(power - 1) / power)
			              + exp * log10(2);
		}
	}

}

int main(){
	double A, curr;
	int B, pos;
	create_table();
	string str;
	while(true){
		cin >> str;
		if(str == "0e0") break;
		pos = str.find('e');
		A = stod(str.substr(0, pos));
		B = stoi(str.substr(pos + 1));
		curr = log10(A) + B;
		for(int ix = 0; ix != 10; ++ix)
			for(int jx = 1; jx <= 30; ++jx)
				if(fabs(curr - table[ix][jx]) <= 1e-5)
					cout << ix << ' ' << jx << endl;
	}
	return 0;
}

#endif
