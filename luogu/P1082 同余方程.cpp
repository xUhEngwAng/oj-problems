#include <cstdio>

/*
 * 原方程可以转化为 ax + by = 1，当然这里的 y 应该是一个负数。
 * 为了解这个方程可以想到扩展的欧几里得算法，由于题目保证一定
 * 有解，因此 gcd(a, b) = 1，即 a, b 一定互素。
 *
 * 解到了一组 x, y 之后，并不能保证 x 是最小的正整数解。实际上，
 * x + kb, y + ka 也是原方程的解，因此在 [0, b] 范围内 x 只有
 * 唯一的取值，将解到的 x 调整到这个范围内即可。
 *
 * 我的调整方案是比较脑残的，用了两个循环：
 *
 * while(x <= 0) x += b;
 * while(x > b)  x -= b;
 *
 * 看了大佬的题解，直接令 x = (x % b + b) % b 就结束了，果然
 * 还是道行不够啊。
 *
 * 这里求出的 x 其实就是在 mod b 意义下 a 的逆元。
 */

void exgcd(int a, int b, long long &x, long long &y){
	long long t;
	if(b == 0){
		x = 1;
		y = 0;
	}else{
		exgcd(b, a % b, x, y);
		t = x;
		x = y;
		y = t - a / b * y;
	}
}

int main(){
	int a, b;
	scanf("%d %d", &a, &b);
	long long x, y;
	exgcd(a, b, x, y);
	while(x <= 0) x += b;
	while(x > b)  x -= b;
	printf("%d\n", x);
	return 0;
}
