#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

bool isSame(string str){
	bool res = true;
	for(char ch : str)
		if(ch != str[0]){
			res = false;
			break;
		}
	return res;
}

int main(){
	string first, second, N;
	int firstNum, secondNum, res;
	cin >> N;
	while(N.size() < 4) N.push_back('0');
	sort(N.begin(), N.end());
	if(isSame(N)){
		cout << N << " - " << N << " = " << "0000" << endl;
		return 0;
	}
	while(true){
		second.assign(N.begin(), N.end());
		first.assign(N.rbegin(), N.rend());
		firstNum = stoi(first);
		secondNum = stoi(second);
		res = firstNum - secondNum;
		N = to_string(res);
		while(N.size() < 4) N.insert(N.begin(), '0');
		cout << first << " - " << second << " = " << N << endl;
		if(N == "6174") break;
		sort(N.begin(), N.end());
	}
	return 0;
}
