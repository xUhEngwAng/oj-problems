#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

/*
 * 这个题的题意不过是求杨辉三角的第 n 行，判断其中每个元素是否
 * 可以整除 m，然而这里的 n 太大了，C(n, k) 很容易就爆了 long
 * long。 
 *
 * 由于 C(n, k) = C(n, k - 1) * (n - k + 1) / k，考虑将除以 k
 * 转化为乘以 k 在 mod m 意义下的逆元，这需要使用扩展的欧几里得
 * 算法。然而该逆元却未必存在，比如 gcd(k, m) != 1 时就不存在。
 *
 * 还有一种策略就是利用杨辉三角的公式，利用 n - 1 相邻的两个元素
 * 来得到第 n 行的元素，此时倒是可以直接取模了，但是时间复杂度为
 * O(n ^ 2)，肯定是会超时的。
 *
 * 我的思路就到了这里，之后学习一下紫书的题解。实际上，我太纠结于
 * 取模了，这里真正关心是每个元素是否整除 m 啊！这个问题之前是学
 * 过的，用质因数分解就可以了。于是我又写了线性筛算法，为了方便
 * 更新与比较用了一个 unordered_map 来保存每一项的质因数及其指数，
 * 结果还是严重超时.......
 *
 * 实际上，我其实并不用求出所有素数，因为这里关心的是是否整除 m，
 * 所以我只用求出组成 m 的素数，对于每一项，也只用这些素数对它们
 * 进行分解。这里 m 的素数不超过 30 个吧，所以时间复杂度大大降低了。
 * 最终只用了 100ms，确实够狠啊。
 */

vector<int> ans;
int prime[40], curr[40], decmp_m[40], pos;

void init(int m){
	int cnt;
	pos = 0;
	for(int ix = 2; ix != 40000; ++ix){
		cnt = 0;
		while(m % ix == 0){cnt++; m = m / ix;}
		if(cnt){
			prime[pos] = ix;
			decmp_m[pos++] = cnt;
		}
		if(m == 1) break;
	}
	if(m != 1){
		prime[pos] = m;
		decmp_m[pos++] = 1;
	}
}

void decomp(int n, bool flag){
	int cnt;
	for(int ix = 0; ix != pos; ++ix){
		cnt = 0;
		while(n % prime[ix] == 0) {cnt++; n = n / prime[ix];}
		if(cnt)
			if(flag) curr[ix] += cnt;
			else     curr[ix] -= cnt;
	}
}

int main(){
	//freopen("1.out", "w", stdout);
	int m, n, p;
	int cnt;
	bool flag;
	while(scanf("%d %d", &n, &m) == 2){
		init(m);
		memset(curr, 0, sizeof(curr));
		ans.clear();
		cnt = 0;
		for(int k = 1; k != n; ++k){
			decomp(n - k, true);
			decomp(k, false);
			flag = true;
			for(int ix = 0; ix != pos; ++ix)
				if(curr[ix] < decmp_m[ix]){
					flag = false;
					break;
				}
			if(flag){
				cnt++;
				ans.push_back(k + 1);
			}
		}
		printf("%d\n", cnt);
		if(cnt) printf("%d", ans[0]);
		for(int ix = 1; ix < ans.size(); ++ix)
			printf(" %d", ans[ix]);
		printf("\n");
	}
	return 0;
}
