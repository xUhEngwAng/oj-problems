#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

/*
 * 这个题我一开始也在想是不是可以通过判断符号来直接得出结果，
 * 从而避免手写大数，但是最大输入 2^63 直接就溢出了啊，确实
 * 想不出比较好的办法。最终只好写了大数，没想到一次就通过了，
 * 佩服我自己！
 *
 * 然后去网上找大家的题解，不是用大数的感觉都有问题啊，他们
 * 都直接用 long long 来存储输入的 a, b, c，然而这里可能直
 * 接就溢出了啊。只能说 PAT 的数据确实垃圾，没有这种边界情况。
 */

bool gt(string one, string two){
	bool ng1 = false, ng2 = false;
	if(one.front() == '-'){
		ng1 = true;
		one.erase(one.begin());
	}
	if(two.front() == '-'){
		ng2 = true;
		two.erase(two.begin());
	}
	if(ng1 && !ng2) return false;
	if(!ng1 && ng2) return true;
	bool res;
	if(one.size() > two.size()) res = true;
	else
	if(one.size() < two.size()) res = false;
	else res = (one > two);
	if(ng1) return !res;
	return res;
}

string add_unsigned(const string &one, const string &two){
	string res;
	int carry = 0, ix, jx, first, second, curr;
	ix = one.size() - 1, jx = two.size() - 1;
	for(; ix >= 0 || jx >= 0; --ix, --jx){
		first  = (ix >= 0? one[ix] - '0': 0);
		second = (jx >= 0? two[jx] - '0': 0);
		curr = first + second + carry;
		if(curr >= 10){
			curr -= 10;
			carry = 1;
		}else carry = 0;
		res.push_back(curr + '0');
	}
	if(carry) res.push_back('1');
	reverse(res.begin(), res.end());
	return res;
}

string sub_unsigned(const string &one, const string &two){
	string res;
	int carry = 0, ix, jx, first, second, curr;
	ix = one.size() - 1, jx = two.size() - 1;
	for(; ix >= 0 || jx >= 0; --ix, --jx){
		first  = (ix >= 0? one[ix] - '0': 0);
		second = (jx >= 0? two[jx] - '0': 0);
		curr   = first - second - carry;
		if(curr < 0){
			curr += 10;
			carry = 1;
		}else carry = 0;
		res.push_back(curr + '0');
	}
	//assert(gt(one, two)), so carry = 0 at this point
	return res;
}

string add(string one, string two){
	string res;
	bool ng1 = false, ng2 = false, ng;
	if(one.front() == '-'){
		ng1 = true;
		one.erase(one.begin());
	}
	if(two.front() == '-'){
		ng2 = true;
		two.erase(two.begin());
	}
	if(ng1 && ng2){
		res.push_back('-');
		res += add_unsigned(one, two);
	}else
	if(ng1 && !ng2){
		if(gt(one, two)){
			res.push_back('-');
			res += sub_unsigned(one, two);
		}
		else res = sub_unsigned(two, one);
	}
	else
	if(!ng1 && ng2){
		if(gt(one, two)) res = sub_unsigned(one, two);
		else{
			res.push_back('-');
			res += sub_unsigned(two, one);
		}
	}
	else res = add_unsigned(one, two);
	return res;
}

int main(){
	int T;
	cin >> T;
	string A, B, C;
	for(int ix = 1; ix <= T; ++ix){
		cin >> A >> B >> C;
		cout << "Case #" << ix << ": ";
		if(gt(add(A, B) , C)) cout << "true"  << endl;
		else                  cout << "false" << endl;
	}
	return 0;
}
