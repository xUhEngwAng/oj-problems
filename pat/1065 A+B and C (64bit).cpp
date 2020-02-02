#include <string>
#include <iostream>
using namespace std;

string add(string one, string two){
	int m = one.size(), n = two.size();
	bool resNega = false, oneNega = false, twoNega = false;
	if(one[0] == '-' && two[0] == '-') resNega = true;
	if(one[0] == '-'){
		oneNega = true;
		one.erase(one.begin());
	}
	if(two[0] == '-'){
		twoNega = true;
		two.erase(two.begin());
	}

	int carry = 0, left, right, ans;
	string res;
	for(int ix = m - 1, jx = n - 1; ix >= 0 || jx >= 0; --ix, --jx){
		left = (ix < 0? 0: one[ix] - '0');
		right = (jx < 0? 0: two[jx] - '0');
		if(!resNega && oneNega) left *= -1;
		if(!resNega && twoNega) right *= -1;
		ans = left + right + carry;
		if(ans >= 10){
			ans -= 10;
			carry = 1;
		}else if(ans < 0){
			ans += 10;
			carry = -1
		}else carry = 0;
		res.push_back(ans + '0');
	}
	if(carry == '1') res.push_back('1');
	if(carry == '-1'){
		
		resNega = true;
	}
	reverse(res.begin(), res.end());
	return res;
}

bool gt(string one, string two){
	if(one.size() > two.size()) return true;
	else
	if(one.size() < two.size()) return false;
	else return one > two;
}

int main(){
	int T;
	cin >> T;
	string A, B, C;
	for(int ix = 1; ix <= T; ++ix){
		cin >> A >> B >> C;
		cout << "Case #" << ix << ' ' << gt(add(A, B), C) << endl;
	}
	return 0;
}
