#include <string>
#include <iostream>
using namespace std;

/*
 * 这个题倒是非常简单，我又是暴力枚举做的......只不过只是
 * 枚举了从 input - 9 * len ~ input - 1 这些数字，所以
 * 没有超时。但是这样时间消耗也挺高了，一共用了 270 ms。
 *
 * 看紫书上给出的解答，比我巧妙不少。是对于 1 ~ 10,000 的
 * 所有元素，逐个计算它们的 digit_sum，并且存储起来。这样
 * 对于每一个查询都可以在 O(1) 时间内获得结果，不可谓不高效。
 *
 * 后面写了紫书上面的版本，确实快了不少，只用了 20 ms 就
 * 跑完了，快了大约有 13 倍了。
 */

int digit_sum(int num){
	int res = num;
	string str = to_string(num);
	for(char ch : str)
		res += ch - '0';
	return res;
}

int main(){
	int N, number, len, res, start;
	bool flag;
	cin >> N;
	string input;
	while(N--){
		cin >> input;
		len = input.size();
		number = stoi(input);
		start = number - 9 * len;
		if(start < 0) start = 0;
		flag = false;
		for(; start < number; ++start){
			res = digit_sum(start);
			if(res == number){
				flag = true;
				break;
			}
		}
		if(flag) cout << start << endl;
		else     cout << 0   << endl;
	}
	return 0;
}

#include <cstdio>
#include <vector>
#include <string>
using namespace std;

vector<int> arr(100100, 0);

int main(){
	int N, sum;
	scanf("%d", &N);
	for(int ix = 1; ix != 100000; ++ix){
		sum = digit_sum(ix);
		if(arr[sum] == 0)
			arr[sum] = ix;
	}
	int curr;
	while(N--){
		scanf("%d", &curr);
		printf("%d\n", arr[curr]);
	}
	return 0;
}
