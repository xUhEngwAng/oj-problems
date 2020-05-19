#include <cstdio>
#define P (10056)

/*
 * 就假设第一名有 i 匹马，可以得到和紫书上相同的结论。这里有一个
 * 问题是 n = 1000 时，组合数太大。我是利用杨辉三角的递推公式
 * 来做的，由于每一项都用得上，实际上也没有浪费效率。
 */

int C[1001][1001], dp[1001];

void init(){
	C[1][0] = C[1][1] = 1;
	C[1][2] = 0;
	for(int ix = 2; ix <= 1000; ++ix){
		C[ix][0] = 1;
		for(int jx = 1; jx <= ix; ++jx)
			C[ix][jx] = (C[ix-1][jx] + C[ix-1][jx-1]) % P;
		C[ix][ix+1] = 0;
	}

	/*for(int ix = 1; ix <= 10; ++ix){
		for(int jx = 0; jx <= ix; ++jx)
			printf("%d ", C[ix][jx]);
		printf("\n");
	}*/

	dp[0] = dp[1] = 1;
	for(int ix = 2; ix <= 1000; ++ix){
		dp[ix] = 0;
		for(int jx = 1; jx <= ix; ++jx)
			dp[ix] = (dp[ix] + C[ix][jx] * dp[ix-jx]) % P;
	}
}

int main(){
	int T, n;
	scanf("%d", &T);
	init();
	for(int ix = 1; ix <= T; ++ix){
		scanf("%d", &n);
		printf("Case %d: ", ix);
		printf("%d\n", dp[n]);
	}
	return 0;
}
