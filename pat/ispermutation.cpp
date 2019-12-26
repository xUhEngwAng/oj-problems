#include <iostream>
#include <vector>
#include <string>
#define RADIX 10
using namespace std;
int main(){
	string digitStr;
	cin >> digitStr;
	vector<int> strCount(10,0), doubledCount(10,0);
	int digitc;
	for(auto c : digitStr){	// count digitStr
		digitc = c - '0';
		strCount[digitc] += 1;
	}
	long long digitStrVal = 0, doubled, temp;
	int idx = digitStr.size() - 1;
	for(auto c : digitStr){ // calculate digitStr
		digitc = c - '0';
		digitStrVal += pow(RADIX, idx)* digitc;
		idx -= 1;
	}
	doubled = digitStrVal * 2;
	temp = doubled;
	int mod;
	do{
		mod = doubled % 10;
		doubled = doubled / 10;
		doubledCount[mod] += 1;
	}while(doubled != 0);
	if(doubledCount == strCount) cout << "Yes" << endl;
	else                         cout << "No"  << endl;
	cout << temp << endl;
	return 0;
}	