#include <cstdio>
#include <cstring>
#define MAXN (100000001)

/*
 * 这题就是线性筛的模板题，我顺便还写了埃氏筛的版本，所有测试
 * 点都超时了......
 *
 * 这里主要总结一下线性筛算法的原理吧。为了找出 n 以内的所有
 * 素数，只需从 2 依次枚举正整数，并且将它们的倍数筛掉，这就
 * 是最原始的筛法，时间复杂度为 O(nlogn)。
 *
 * 实际上，并不需要筛掉这些正整数的全部倍数，而只用考虑素数倍
 * 的倍数，这是因为非素数都可以被前面的素数表示，此时代码如下：
 *
 * for(int i = 2; i <= n; ++i){
 *     if(!vis[i]) prime[pos++] = i;
 *     for(int j = 1; j < pos && prime[j]*i <= n; ++j)
 *         vis[prime[j]*i] = true;
 * }
 *
 * 每次内循环都只考虑了小于等于 i 的素数倍，这类似于埃氏筛中
 * 从 j = i * i 开始内循环，实际上上述代码只是将埃氏筛代码中
 * 的两个循环交换了次序而已，时间复杂度为 O(nloglogn)，但是我
 * 不会证明。
 *
 * 此时，一个合数仍然会被筛掉多次，比如 12 = 2 * 6 = 3 * 4，
 * 会被筛掉两次。为了避免重复，线性筛保证每个数只被其最小的素
 * 因子筛掉，其实现只需要在上述代码的内循环最后加上
 *
 * if(i % prime[j] == 0) break;
 *
 * 如果条件第一次成立，则说明 i 的最小素因子为 prime[j]，下
 * 循环筛掉的整数为 i * prime[j + 1]，显然 prime[j + 1] 并
 * 非该数的最小素因子，因此存在重复，所以条件成立时 break。
 */

bool visited[MAXN];
int prime[MAXN / 10];

void init(int n){
	memset(visited, 0, sizeof(bool) * (n + 1));
	int pos = 0;
	for(int i = 2; i <= n; ++i){
		if(!visited[i]) prime[pos++] = i;
		for(int j = 1; j < pos && prime[j] * i <= n; ++j){
			visited[prime[j] * i] = true;
			if(i % prime[j] == 0) break;
		}
	}
}

void init1(long long n){
	memset(visited, 0, sizeof(bool) * (n + 1));
	int pos = 0;
	long long jx;
	for(int ix = 2; ix <= n; ++ix){
		if(visited[ix]) continue;
		prime[pos++] = ix;
		jx = (long long)ix * ix;
		//printf("%lld\n", jx);
		for(; jx <= n; jx += ix)
			visited[jx] = true;
	}
}

int main(){
	int n, q;
	scanf("%d %d", &n, &q);
	init1(n);
	int query;
	for(int ix = 0; ix != q; ++ix){
		scanf("%d", &query);
		printf("%d\n", prime[query - 1]);
	}
	return 0;
}
