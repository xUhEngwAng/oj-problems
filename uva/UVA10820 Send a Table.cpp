#include <cstdio>
#define MAXN (50001)

/*
 * 这个题是用到了欧拉函数(phi 函数)，没有学过这个的话应该够呛。
 *
 * 我这里简单说明一下。用 phi(n) 表示 [1, n] 中与 n 互素的元素
 * 数量，这里互素的定义是 gcd(x, y) = 1。这样的话，本题要求的
 * 答案就是 phi(1) + 2(phi(2) + phi(3) + ... + phi(n))，因为
 * x, y 是可以交换的。
 *
 * 接下来的问题就是如何求 phi(n) 了。实际上设 n 的质因子有 p1, 
 * p2, ..., pk，那么 phi(n) = n(1 - 1/p1)(1 - 1/p2)...(1 - 1/pk)
 * 可以利用类似与埃氏筛的算法，在 O(n loglogn) 时间内算出 phi(1)
 * 乃至 phi(n)。
 */

int phi[MAXN], res[MAXN];

void init(){
	for(int ix = 1; ix != MAXN; ++ix) phi[ix] = ix;
	for(int ix = 2; ix != MAXN; ++ix){
		if(phi[ix] != ix) continue;
		for(int jx = ix; jx < MAXN; jx += ix)
			phi[jx] = phi[jx] / ix * (ix - 1);
	}

	res[1] = phi[1];
	for(int ix = 2; ix != MAXN; ++ix)
		res[ix] = res[ix-1] + 2 * phi[ix];
}

int main(){
	int N;
	init();
	while(scanf("%d", &N) == 1){
		if(N == 0) break;
		printf("%d\n", res[N]);
	}
	return 0;
}
