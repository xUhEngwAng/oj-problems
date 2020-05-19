#include <cstdio>
#include <cstring>

/*
 * 这个题我是想出了一种特别复杂的递推公式，因为太复杂了，我都
 * 懒得就测试样例验算一遍，直接就开始 coding 了，本来想有一堆
 * bug 等着调试，结果它就，过了？！小说都不敢这么写，希望机试
 * 的时候也能这样如有神助。
 *
 * 设 d(n, l, r) 为 n 根杆子排成一行，从左边看有 l 个，从右边
 * 看有 r 个的组合数量。枚举最高杆子的位置 k(1 <= k <= n)，此
 * 时左边还有 k - 1 根杆子，需要看到其中的 l - 1 个；右边还有
 * n - k 根杆子，需要看到其中的 r - 1 个。记 f(n, l) 为 n 根
 * 杆子中，从左侧（左右对称）看到 l 根杆子的组合数量，所以有
 *
 * dp(n, l, r) = \Sigma C(n-1, k-1) * f(k-1, l-1) * f(n-k, r-1)
 *
 * 往下的问题就是如何求到 f(n, l) 了。同样枚举最高杆子的位置 k，
 * 此时右侧的 n-k 根杆可以任意组合，左侧等价于 f(k-1, l-1)，故
 * 
 * f(n, k) = \Sigma f(k-1, l-1) * C(n-1, k-1) * (n-k)!
 *
 * 这里需要注意边界条件，即 f(0, 0) = 1, f(0, k) = 0 (k > 0)
 *
 * 当然了，lrj 大神的递推公式比我简单多了......它的基本思想是
 * 在安排好 2-i 的杆子后，才来安排最短的杆子。不难看出，
 *
 * d(n, l, r) = d(n-1, l-1, r) + d(n-1, l, r-1) + (n-2)d(n-1,l, r)
 *
 * 上式三项分别表示最短杆子在最左侧，最右侧，以及在中间的情形。
 */

long long dp[21][21], fac[20];
int C[20][20];

void init(){
	C[0][0] = 1;C[0][1] = 0;
	for(int ix = 1; ix != 20; ++ix){
		C[ix][0] = 1;
		for(int jx = 1; jx <= ix; ++jx)
			C[ix][jx] = C[ix-1][jx-1] + C[ix-1][jx];
		C[ix][ix+1] = 0;
	}
	fac[0] = 1;
	for(int ix = 1; ix != 20; ++ix)
		fac[ix] = fac[ix-1] * ix;

	memset(dp, sizeof(dp), 0);
	dp[0][0] = 1;
	for(int ix = 1; ix <= 20; ++ix){
	for(int jx = 1; jx <= ix; ++jx)
	for(int kx = 1; kx <= ix; ++kx)
		dp[ix][jx] += dp[kx-1][jx-1] * C[ix-1][kx-1] * fac[ix-kx];
	}
}

long long compute(int n, int l, int r){
	long long ret = 0;
	for(int kx = 1; kx <= n; ++kx)
		ret += C[n-1][kx-1] * dp[kx-1][l-1] * dp[n-kx][r-1];
	return ret;
}

int main(){
	int T, n, l, r;
	scanf("%d", &T);
	init();
	while(T--){
		scanf("%d %d %d", &n, &l, &r);
		printf("%lld\n", compute(n, l, r));
	}
	return 0;
}
