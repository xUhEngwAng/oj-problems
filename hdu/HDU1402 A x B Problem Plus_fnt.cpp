#include <string>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

/*
 * 这个题兜兜转转，总算是通过了！
 *
 * 这里我犯了很多很多低级错误，导致我调试了很长的时间。一开始
 * 是快速幂函数写错了，power 的更新写成了power = power * base，
 * 可见快速幂的实现还是不熟悉。
 *
 * 然后又调了半天，发现我的 P 写错了......所以这个数字还是要
 * 记清楚才是啊。然而还是有问题，才发现调用 pow 时根本没有调用
 * 我实现的快速幂，而是 built-in 的pow函数，改了个名字就好了。
 *
 * 最后还做了一些探索。一开始我更新 gn_reverse 是下面这样
 *
 * gn_reverse[ix] = pow(gn[ix], P - 2);
 *
 * 这固然是可以的，但我觉得还是有点浪费开销。实际上，由于
 *
 * gn[ix] * gn[n - ix] = 1 (mod P)
 *
 * 直接令 gn_reverse[n - ix] = gn[ix] 就可以了。
 *
 * 一开始我是用 fft 来做这个题的，不知道是不是精度的原因，一直
 * 没有通过。
 */

#define P    (998244353)
#define G    (3)
#define MAXN (1 << 17)

long long gn[MAXN], gn_reverse[MAXN];
long long a[MAXN], b[MAXN];

long long fpow(long long base, int n){
	long long power = base;
	long long res = 1;
	while(n){
		if(n & 1) res = (res * power) % P;
		power = (power * power) % P; 
		n = n >> 1;
	}
	return res;
}

void init(int n){
	long long g = fpow(G, (P - 1) / n);
	gn[0] = gn_reverse[0] = 1;
	for(int ix = 1; ix != n; ++ix){
		gn[ix] = (g * gn[ix - 1]) % P;
		gn_reverse[n - ix] = gn[ix];
	}
}

void fnt(long long *a, int n, int op){
	for(int ix = 0, jx = 0; ix != n; ++ix){
		if(ix > jx) swap(a[ix], a[jx]);
		for(int l = n >> 1; (jx = jx ^ l) < l; l = l >> 1);
	}
	long long z;
	int m;
	for(int ix = 2; ix <= n; ix = ix << 1){
		m = ix >> 1;
		for(int jx = 0; jx != n; jx += ix)
			for(int kx = 0; kx != m; ++kx){
				if(op) 
					z = (a[jx + kx + m] * gn[kx * (n / ix)]) % P;
				else
					z = (a[jx + kx + m] * gn_reverse[kx * (n / ix)]) % P;
				a[jx + kx + m] = (a[jx + kx] + P - z) % P;
				a[jx + kx] = (a[jx + kx] + z) % P;
			}
	}
	if(!op){
		z = fpow(n, P - 2);
		for(int ix = 0; ix != n; ++ix)
			a[ix] = (a[ix] * z) % P;
	}
}

int main(){
	string one, two, res;
	int m, n, len, curr, carry;
	while(cin >> one >> two){
		m = one.size(), n = two.size();
		for(len = 1; len < m + n; len = len << 1);
		init(len);
		memset(a, 0, sizeof(long long) * len);
		memset(b, 0, sizeof(long long) * len);
		for(int ix = 0; ix != m; ++ix)
			a[ix] = one[m - 1 - ix] - '0';
		for(int ix = 0; ix != n; ++ix)
			b[ix] = two[n - 1 - ix] - '0';
		fnt(a, len, 1);
		fnt(b, len, 1);
		for(int ix = 0; ix != len; ++ix)
			a[ix] = (a[ix] * b[ix]) % P;
		fnt(a, len, 0);
		res.clear();
		carry = 0;
		for(int ix = 0; ix != len; ++ix){
			curr = a[ix] + carry;
			carry = curr / 10;
			curr  = curr - 10 * carry;
			res.push_back(curr + '0');
		}
		if(carry) res.push_back(carry + '0');
		while(res.back() == '0') res.pop_back();
		reverse(res.begin(), res.end());
		if(res.empty()) cout << 0 << endl;
		else cout << res << endl;
	}
	return 0;
}
