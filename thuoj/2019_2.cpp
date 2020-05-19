#include <string>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define P     (998244353)
#define G     (3)
long long a[8192], b[8192];
long long gn[8192], gn_reverse[8192];

long long fpow(long long base, int n){
	long long res = 1;
	long long power = base;
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
		if(ix < jx) swap(a[ix], a[jx]);
		for(int l = n >> 1; (jx = jx ^ l) < l; l = l >> 1);
	}
	long long z;
	int m;
	for(int ix = 2; ix <= n; ix = ix << 1){
		m = ix >> 1;
		for(int jx = 0; jx != n; jx += ix)
			for(int kx = 0; kx != m; ++kx){
				if(op) z = (a[jx + kx + m] * gn[kx * (n / ix)]) % P;
				else   z = (a[jx + kx + m] * gn_reverse[kx * (n / ix)]) % P;
				a[jx + kx + m] = (a[jx + kx] - z + P) % P;
				a[jx + kx]     = (a[jx + kx] + z) % P;
			}
	}
	if(!op){
		z = fpow(n, P - 2);
		for(int ix = 0; ix != n; ++ix)
			a[ix] = (a[ix] * z) % P;
	}
}

string add(const string &left, const string &right){
	string ret;
	int one, two, curr, carry = 0;
	for(int ix = left.size() - 1, jx = right.size() - 1; ix >= 0 || jx >= 0; --ix, --jx){
		one = (ix >= 0? left[ix] - '0': 0);
		two = (jx >= 0? right[jx] - '0': 0);
		curr = one + two + carry;
		if(curr >= 10){
			curr -= 10;
			carry = 1;
		}else carry = 0;
		ret.push_back(curr + '0');
	}
	if(carry) ret.push_back('1');
	reverse(ret.begin(), ret.end());
	return ret;
}

string half(const string &str){
	int up = 0, res;
	string ret;
	for(int ix = 0; ix != str.size(); ++ix){
		up = up * 10 + str[ix] - '0';
		res = up / 2;
		up = up - res * 2;
		ret.push_back(res + '0');
	}
	if(ret[0] == '0') return ret.substr(1);
	return ret;
}

string multiply(const string &left, const string &right){
	string ret;
	int m = left.size(), n = right.size();
	int len = 1;
	while(len < m + n) len = len << 1;
	init(len);
	memset(a, 0, len * sizeof(long long));
	memset(b, 0, len * sizeof(long long));
	for(int ix = 0; ix != m; ++ix)
		a[ix] = left[m - 1 - ix] - '0';
	for(int ix = 0; ix != n; ++ix)
		b[ix] = right[n - 1 - ix] - '0';
	fnt(a, len, 1);
	fnt(b, len, 1);
	for(int ix = 0; ix != len; ++ix)
		a[ix] = (a[ix] * b[ix]) % P;
	fnt(a, len, 0);
	int carry = 0, curr;
	for(int ix = 0; ix != m + n; ++ix){
		curr  = a[ix] + carry;
		carry = curr / 10;
		curr  = curr - 10 * carry;
		ret.push_back(curr + '0');
	}
	if(carry) ret.push_back(carry + '0');
	while(ret.back() == '0') ret.pop_back();
	reverse(ret.begin(), ret.end());
	return ret;
}

string pow(const string &str, int exp){
	string ret = str;
	for(int ix = 1; ix != exp; ++ix){
		ret = multiply(ret, str);
	}
	return ret;
}

bool lt(const string &left, const string &right){
	if(left.size() != right.size())
		return left.size() < right.size();
	for(int ix = 0; ix != left.size(); ++ix){
		if(left[ix] != right[ix]) 
			return left[ix] < right[ix];
	}
	return false;
}

int main(){
	//freopen("1.in", "r", stdin);
	string n;
	int m;
	cin >> n >> m;
	string lo = "1", mid, hi = n, curr;
	while(lt(lo, hi)){
		mid = half(add(lo, hi));
		curr = pow(mid, m);
		if(lt(curr, n)) lo = add(mid, "1");
		else if(lt(n, curr)) hi = mid;
		else break;
	}
	cout << mid << endl;
	return 0;
}
