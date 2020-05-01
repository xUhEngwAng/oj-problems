#include <cstdio>
#include <string>
#include <cstring>
using namespace std;

int dp[7][10];

void init(){
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	for(int ix = 1; ix != 7; ++ix)
		for(int jx = 0; jx <= 9; ++jx){
			if(jx == 4) continue;
			for(int kx = 0; kx <= 9; ++kx)
				if(jx != 6 || kx != 2)
					dp[ix][jx] += dp[ix-1][kx];
		}
}

int compute(int n){
	string str = to_string(n);
	int len = str.size();
	int ret = 0;
	for(int ix = 0; ix != len; ++ix){
		for(int jx = 0; jx != str[ix]-'0'; ++jx)
			if(ix == 0 || str[ix-1] != '6' || jx != 2)
				ret += dp[len - ix][jx];
		if(str[ix] == '4' || 
		   (ix > 0 && str[ix-1] == '6' && str[ix] == '2'))
			break;
	}
	return ret;
}

int main(){
	int n, m;
	init();
	while(scanf("%d %d", &n, &m) == 2){
		if(n == 0 && m == 0) break;
		printf("%d\n", compute(m+1) - compute(n));
	}
	return 0;
}
