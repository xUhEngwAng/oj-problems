#include <string>
#include <iostream>
using namespace std;

bool isPalindromic(const string &str){
	int ix = 0, jx = str.size() - 1;
	for(; ix <= jx; ++ix, --jx){
		if(str[ix] != str[jx])
			return false;
	}
	return true;
}

string add(const string& left, const string& right){
	int carry = 0, one, two, curr;
	string tmp;
	int ix = left.size() - 1, jx = right.size() - 1;
	for(; ix >= 0 || jx >= 0; --ix, --jx){
		one = (ix >= 0? left[ix] - '0': 0);
		two = (jx >= 0? right[jx] - '0': 0);
		curr = one + two + carry;
		if(curr >= 10){
			curr -= 10;
			carry = 1;
		}
		else carry = 0;
		tmp.push_back(curr + '0');
	}
	if(carry) tmp.push_back('1');
	string res;
	res.assign(tmp.rbegin(), tmp.rend());
	return res;
}

int main(){
	string input, reverse, res;
	cin >> input;
	int count = 0;
	while(!isPalindromic(input)){
		reverse.assign(input.rbegin(), input.rend());
		res = add(input, reverse);
		cout << input << " + " << reverse << " = " << res << endl;
		input = res;
		if(++count == 10) break;
	}
	if(count == 10) cout << "Not found in 10 iterations." << endl;
	else cout << input << " is a palindromic number." << endl;
	return 0;
}
