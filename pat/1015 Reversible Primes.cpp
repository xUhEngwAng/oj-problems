#include <cstdio>
#include <string>
#include <cmath>
using namespace std;

/*
 * 这个题本身比较简单，但是我开始是没有读懂题的，这里阐述一下。
 * 输入的是一个正整数 N 以及它的基 D，但是其实 N 是十进制的，
 * 需要首先将它转化为 D 进制，然后再做 reserve。我开始的理解
 * 是 N 本身就是 D 进制，于是看样例的 【23 2】 我就懵了：
 * 2 进制的 23？？？
 */

bool isPrime(int num){
	if(num == 1) return false;
	bool res = true;
	int end = sqrt(num);
	for(int ix = 2; ix <= end; ++ix)
		if(num % ix == 0){
			res = false;
			break;
		}
	return res;
}

int convert(int N, int radix){
	string strRes;
	while(N != 0){
		strRes.push_back('0' + N % radix);
		N = N / radix;
	}
	int res = 0, pow = 1;
	for(auto it = strRes.rbegin(); it != strRes.rend(); ++it){
		res += pow * (*it - '0');
		pow *= radix;
	}
	return res;
}

int main(){
	int N, D;
	while(true){
        scanf("%d", &N);
        if(N < 0) break;
        scanf("%d", &D);
		if(isPrime(N) && isPrime(convert(N, D)))
			printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
