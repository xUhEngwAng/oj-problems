#include <string>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

/*
 * 我对题意的理解好像出了一点问题......他说所有数字的
 * 大小都不超过 2^30，我还以为是输入的数字不超过，这样
 * 的话输出很可能就爆 long long 了啊！所以我还手写了
 * 大数加法。看了题解发现它的意思好像是结果的数字也不会
 * 超过 2^30......
 * 不过这个题我发现自己有点变强了，写完代码居然没有报错，
 * 看来语法方面开始熟悉了。
 */

typedef long long ll;

bool cmp(ll one, ll two){
	return one > two;
}

void add(string& rd, const string& rs){
	int m = rd.size(), n = rs.size();
	int one, two, carry = 0, tmp;
	string res;
	for(int ix = m - 1, jx = n - 1; ix >= 0 || jx >= 0; --ix, --jx){
		one = (ix < 0? 0: rd[ix] - '0');
		two = (jx < 0? 0: rs[jx] - '0');
		tmp = one + two + carry;
		if(tmp >= 10){
			tmp -= 10;
			carry = 1;
		}else carry = 0;
		res.push_back(tmp + '0');
	}
	if(carry) res.push_back('1');
	rd.assign(res.rbegin(), res.rend());
}

int main(){
	int Nc, Np;
	vector<ll> neg_coup, pos_coup, neg_pro, pos_pro;
	scanf("%d", &Nc);
	neg_coup.reserve(Nc);
	pos_coup.reserve(Nc);
	ll curr;
	for(int ix = 0; ix != Nc; ++ix){
		scanf("%lld", &curr);
		if(curr < 0) neg_coup.push_back(curr);
		else pos_coup.push_back(curr);
	}
	scanf("%d", &Np);
	neg_pro.reserve(Np);
	pos_pro.reserve(Np);
	for(int ix = 0; ix != Np; ++ix){
		scanf("%lld", &curr);
		if(curr < 0) neg_pro.push_back(curr);
		else if(curr >= 0) pos_pro.push_back(curr);
		else;
	}
	sort(neg_coup.begin(), neg_coup.end());
	sort(pos_coup.begin(), pos_coup.end(), cmp);
	sort(neg_pro.begin(), neg_pro.end());
	sort(pos_pro.begin(), pos_pro.end(), cmp);

	string res;
	ll tmp;
	for(int ix = 0; ix < neg_coup.size() && ix < neg_pro.size(); ++ix){
		tmp = neg_coup[ix] * neg_pro[ix];
		add(res, to_string(tmp));
	}
	for(int ix = 0; ix < pos_coup.size() && ix < pos_pro.size(); ++ix){
		tmp = pos_coup[ix] * pos_pro[ix];
		add(res, to_string(tmp));
	}
	if(!res.empty()) cout << res << endl;
	else cout << 0 << endl;
	return 0;
}
