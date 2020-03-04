#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

string U[5] = {"314882150829468584", "427197303358170108", "1022292690726729920",
               "1698479428772363217", "2006101093849356424"};
const string str = "2009731336725594113";

string add(const string &left, const string &right){
	int one, two, carry = 0, curr;
	string res;
	for(int ix = left.size() - 1, jx = right.size() - 1;
		ix >= 0 || jx >= 0; --ix, --jx){
		one = (ix >= 0? left[ix] - '0': 0);
		two = (jx >= 0? right[jx] - '0': 0);
		curr = one + two + carry;
		carry = curr / 10;
		curr = curr - 10 * carry;
		res.push_back(curr + '0');
	}
	if(carry) res.push_back('1');
	reverse(res.begin(), res.end());
	//cout << res << endl;
	return res;
}

string multiply_onebit(const string &left, int bit){
	int carry = 0, curr;
	string res;
	for(int ix = left.size() - 1; ix >= 0; --ix){
		curr = (left[ix] - '0') * bit + carry;
		carry = curr / 10;
		curr = curr % 10;
		res.push_back(curr + '0');
	}
	if(carry) res.push_back(carry + '0');
	reverse(res.begin(), res.end());
	return res;
}

string multiply(const string left, string right){
	string res;
	for(char ch : right){
		res = add(res, multiply_onebit(left, ch - '0'));
		res.push_back('0');
	}
	res.pop_back();
	return res;
}

bool lt(const string &left, const string &right){
	if(left.size() != right.size())
		return left.size() < right.size();
	return left < right;
}

string subtract(const string &left, const string &right){
	int one, two, carry = 0, curr;
	string res;
	for(int ix = left.size() - 1, jx = right.size() - 1;
		ix >= 0 || jx >= 0; --ix, --jx){
		one = (ix >= 0? left[ix] - '0': 0);
		two = (jx >= 0? right[jx] - '0': 0);
		curr = one - two + carry;
		if(curr < 0){
			curr += 10;
			carry = -1;
		}else carry = 0;
		res.push_back(curr + '0');
	}
	while(res.back() == '0') res.pop_back();
	reverse(res.begin(), res.end());
	return res;
}

string mod(const string &left, const string &right){
	if(lt(left, right)) return left;
	string tmp = left.substr(0, right.size() - 1);
	for(int pos = right.size() - 1; pos != left.size(); ++pos){
		tmp.push_back(left[pos]);
		while(!lt(tmp, right)) tmp = subtract(tmp, right);
	}
	return tmp;
}

int fcn(const string &input){
    string res;
	res = mod(input, str);
	res = mod(res, "2019");
	return stoi(res);
}

int main(){
	int n, q;
	scanf("%d %d", &n, &q);
	vector<string> seq(n + 1);
	for(int ix = 1; ix <= n; ++ix)
		seq[ix] = to_string(ix);
	int left, right, res, pos;
	while(q--){
        res = 0;
		scanf("%d %d", &left, &right);
		for(int ix = left; ix <= right; ++ix)
			res += fcn(seq[ix]);
		printf("%d\n", res);
		pos = res % 5;
		for(int ix = left; ix <= right; ++ix)
			seq[ix] = multiply(seq[ix], U[pos]);
	}
	return 0;
}
