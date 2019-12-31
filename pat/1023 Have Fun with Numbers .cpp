#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

string doubleStr(string str){
	string res;
	int carry = 0, len = str.length(), digit;
	for(int ix = len - 1; ix >= 0; --ix){
		digit = ((str[ix] - '0') << 1) + carry;
		if(digit >= 10){
			carry = 1;
			digit -= 10;
		}
		else carry = 0;
		res.push_back(digit + '0');
	}
	if (carry) res.push_back('1');
	reverse(res.begin(), res.end());
	return res;
}

int main(){
	string input, output;
	cin >> input;
	output = doubleStr(input);
	string tmp = output;
	sort(input.begin(), input.end());
	sort(output.begin(), output.end());
	if (input == output) cout << "Yes" << endl;
	else                 cout << "No" << endl;
	cout << tmp << endl;
	system("pause");
	return 0;
}
