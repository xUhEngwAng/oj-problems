#include <string>
#include <iostream>
using namespace std;

/*
 * 一开始犯了一个小错误：把 res.clear 放在了内层循环
 * 的外面。这样某一个 input 结束后，下一个输入的字符串
 * 将得到一个初始非空的 res，因而引起潜在的错误。把
 * res.clear 放在循环开始处就没有问题了。
 */

int main(){
	string input, pattern, res;
	int N, len, cnt;
	cin >> N;
	while(N--){
		cin >> input;
		for(len = 1; len <= input.size(); ++len){
            res.clear();
			if(input.size() % len) continue;
			pattern = input.substr(0, len);
			cnt = input.size() / len;
			while(cnt--)
				res += pattern;
			if(input == res){
				cout << len << endl;
				if(N) cout << endl;
				break;
			}
		}
	}
	return 0;
}
