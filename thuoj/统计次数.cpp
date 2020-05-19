#include <cstdio>
#include <string>
#include <cstring>
using namespace std;
int dp[8][10];

// copy from 自己做的快速幂模板
int fpow(int base, int exp){
	int ret = 1, power = base;
	while(exp){
		if(exp & 1) ret = ret * power;
		power = power * power;
		exp = exp >> 1;
	}
	return ret;
}

void init(int k){
	memset(dp, 0, sizeof(dp));
	for(int ix = 1; ix <= 7; ++ix)
		for(int jx = 0; jx <= 9; ++jx){
			if(jx == k)
				dp[ix][jx] += fpow(10, ix - 1);
			for(int kx = 0; kx <= 9; ++kx)
				dp[ix][jx] += dp[ix-1][kx];
		}
}

int compute(int n, int k){
	int ret = 0, tmp, cnt = 0;
	string str = to_string(n);
	//copy from 自己做的数位 dp 模板
	for(int ix = 0; ix != str.size(); ++ix){
		tmp = fpow(10, str.size() - ix - 1);
		for(int jx = 0; jx != str[ix] - '0'; ++jx){
			ret += dp[str.size() - ix][jx];
			ret += cnt * tmp;
		}
		if(str[ix] - '0' == k) cnt++;
	}
	return ret;
}

int main(){
	int n, k;
	scanf("%d %d", &n, &k);
	init(k);
	printf("%d\n", compute(n+1, k));
	return 0;
}
