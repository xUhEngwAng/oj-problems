#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

int dp[11][10][2][12];

int fast_pow(int base, int exp){
	int ret = 1, power= base;
	while(exp){
		if(exp & 1) ret = (ret * power) % 13;
		power = (power * power) % 13;
		exp = exp >> 1;
	}
	return ret;
}

void init(){
	int mod;
	memset(dp, 0, sizeof(dp));
	for(int j = 0; j <= 9; ++j) 
		dp[1][j][0][j] = 1;
	for(int ix = 2; ix <= 10; ++ix)
	for(int j = 0; j <= 9; ++j)
	for(int l = 0; l <= 12; ++l){
		mod = (l - ((j*fast_pow(10, ix-1)) % 13) + 13) % 13;
		for(int k = 0; k <= 9; ++k){
			if(j != 1 || k != 3)
				dp[ix][j][0][l] += dp[ix-1][k][0][mod];
			dp[ix][j][1][l] += dp[ix-1][k][1][mod];
			if(j == 1 && k == 3)
				dp[ix][j][1][l] += dp[ix-1][k][0][mod];
		}
	}
}

int compute(int n){
	string str = to_string(n);
	int res = 0, mod = 0;
	bool flag = false;
	for(int ix = 0; ix != str.size(); ++ix){
		for(int jx = 0; jx != str[ix] - '0'; ++jx){
			res += dp[ix][jx][1][(13-mod) % 13];
			if(!flag && (jx == 3 && ix > 0 && str[ix-1] == '1'))
				res += dp[ix][jx][0][(13-mod) % 13];
			if(flag)
				res += dp[ix][jx][0][(13-mod) % 13];
		}
		if(ix > 0 && str[ix-1] == '1' && str[ix] == '3')
			flag = true;
		mod = (mod + (str[ix] - '0') * fast_pow(10, str.size() - ix - 1)) % 13;
	}
	return res;
}

int main(){
	int n;
	init();
	while(scanf("%d", &n) == 1){
		printf("%d\n", compute(n));
	}
	return 0;
}
