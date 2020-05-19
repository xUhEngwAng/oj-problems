#include <string>
#include <iostream>
#include <cstring>
#define P (20123)
using namespace std;

int dp[101][10];

int fast_pow(int base, int exp){
	int ret = 1, power= base;
	while(exp){
		if(exp & 1) ret = (ret * power) % P;
		power = (power * power) % P;
		exp = exp >> 1;
	}
	return ret;
}

void init(){
	memset(dp, 0, sizeof(dp));
	for(int ix = 1; ix <= 100; ++ix)
		for(int jx = 0; jx <= 9; ++jx){
			if(jx == 1 || jx == 2)
				dp[ix][jx] += fast_pow(10, ix - 1);
			for(int kx = 0; kx <= 9; ++kx)
				dp[ix][jx] += dp[ix-1][kx];
			dp[ix][jx] = dp[ix][jx] % P;
		}
}

int compute(string n){
	int ret = 0, tmp, cnt = 0;
	for(int ix = 0; ix != n.size(); ++ix){
		tmp = fast_pow(10, n.size() - ix - 1);
		for(int jx = 0; jx != n[ix] - '0'; ++jx){
			ret += dp[n.size() - ix][jx];
			ret += cnt * tmp;
		}
		if(n[ix] == '1' || n[ix] == '2') cnt++;
		ret = ret % P;
	}
	return ret;
}

string inc(string input){
	int curr, carry = 1;
	for(int ix = input.size() - 1; ix >= 0; --ix){
		curr = input[ix] - '0' + carry;
		carry = curr / 10;
		curr = curr - carry * 10;
		input[ix] = curr + '0';
		if(!carry) break;
	}
	if(carry) input.insert(input.begin(), '1');
	return input;
}

int main(){
	string n;
	init();
	while(cin >> n){
		//cout << inc(n) << endl;
		cout << compute(inc(n)) << endl;
	}
	return 0;
}
