#include <string>
#include <iostream>
using namespace std;

int main(){
	string N;
	cin >> N;
	int pow = 1, count = 0, len = N.size();
	int leftNum, rightNum;
	char curr;
	string left, right;
	for(int ix = len - 1; ix >= 0; --ix){
		curr = N[ix];
		left = N.substr(0, ix);
		right = N.substr(ix + 1, len);
		leftNum = (left.empty()?0: stoi(left));
		rightNum = (right.empty()?0: stoi(right));
		if(curr >= '2')
			count += (leftNum + 1) * pow;
		else if(curr == '1')
			count += leftNum * pow + rightNum + 1;
		else
			count += leftNum * pow;
		pow = pow * 10;
	}
	cout << count << endl;
	return 0;
}
