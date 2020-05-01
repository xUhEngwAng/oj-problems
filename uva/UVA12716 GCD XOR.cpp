#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
#define MAXN (30000001)

/*
 * 做这种题就让人很头大，这就仿佛它在第五层，而我连第一层都想不
 * 到。
 *
 * 比较 naive 的想法就是单纯用一个前缀数组，对于每一个 a， 枚举
 * 所有的 b <= a，判断 gcd(a, b) == (a ^ b) 是否成立。由于 gcd
 * 的时间复杂度有 O(logn)，整体时间复杂度为 O(n^2 logn)，n = 3e7
 * 时大约要跑到明年。
 *
 * 接下来的都是我想不到的......
 *
 * 1. 第一次优化，考虑抑或的性质，如果 c = a^b，则 b = a^c，这
 *    可以举个例子自己就证明了。因此对于每一个 a， 可以枚举它的
 *    因数 c，由此计算出 b，然后判断 c == gcd(a, b) 是否成立，
 *    该方案的时间复杂度为 O(n * logn * logn)，还是会超时。
 *
 * 2. 第二次优化。首先证明 a ^ b >= a - b，因为对于每一位，该式
 *    都成立，所以整体也成立，所以 c >= a - b；另一方面，c = 
 *    gcd(a, b)，所以 gcd(a/c, b/c) = 1，当 a > b 时，a/c - b/c
 *    >= 1，所以 c <= a - b. 显然 a == b 时，并不满足题意。所以
 *    c = a - b.
 *
 *    我看不少题解直接就把这个结论拿来用了，须知 c = a - b 只是
 *    满足题意的必要条件，还需要证明它是充分的才行啊。当 c 是 a
 *    的因子时，b = a - c 显然整除 c，而 gcd(a/c, b/c) = 1,故
 *    gcd(a, b) = c，往下只需验证 c = a ^ b 即可。因此这里避免
 *    了 gcd 运算的复杂度。该方案的时间复杂度为 O(n logn)。
 *
 * 然后我就写出了我的代码，简单说来先把每一个数的所有因数存储起来，
 * 这类似于埃氏筛算法，然后对于每一个 a，依次枚举它的因数 c，验证
 * 是否满足 a ^ (a - c) = c，然后这个算法也超时严重，大约需要 10s.
 *
 * 然后看了大佬的代码，并没有保存每个数的因数，而是枚举 c， 然后
 * 枚举 c 的倍数作为 a，做验证即可。这种算法只需要 1s 就可以跑完了，
 * 可见存储的开销还是大啊。
 */

int ans[MAXN];
vector<int> devisor[MAXN];

void init_(){
	for(int ix = 1, jx; (jx = ix << 1) < MAXN; ++ix)
		for(; jx < MAXN; jx += ix)
			devisor[jx].push_back(ix);
	ans[1] = 0;
	int temp, b;
	for(int ix = 2; ix != MAXN; ++ix){
		temp = 0;
		for(int e : devisor[ix]){
			b = ix - e;
			//printf("c = %d, a ^ b = %d\n", e, ix ^ b);
			if(e == (ix ^ b)) temp++;
		}
		ans[ix] = ans[ix-1] + temp;
		//printf("ans[%d]: %d\n", ix, ans[ix]);
	}
}

void init(){
	int b;
	memset(ans, 0, sizeof(ans));
	for(int ix = 1, jx; (jx = ix << 1) < MAXN; ++ix)
		for(; jx < MAXN; jx += ix){
			b = jx - ix;
			if((jx ^ b) == ix) ans[jx]++;
		}
	for(int ix = 2; ix != MAXN; ++ix)
		ans[ix] += ans[ix-1];
}

int main(){
	init();
	int T, N;
	scanf("%d", &T);
	for(int ix = 1; ix <= T; ++ix){
		scanf("%d", &N);
		printf("Case %d: ", ix);
		printf("%d\n", ans[N]);
	}
	return 0;
}
