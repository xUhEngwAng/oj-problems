#include <cstdio>
#include <iostream>
using namespace std;

int arr[200];

int gcd(int one, int two){
	if(two == 0) return one;
	return gcd(two, one % two);
}

void exgcd(int a, int b, long long &x, long long &y){
	if(b == 0){
		x = 1;
		y = 0;
		return;
	}
	exgcd(b, a % b, x, y);
	long long t = x;
	x = y;
	y = t - a / b * y;
}

int main(){
	freopen("1.out", "w", stdout);
	int T, a, c, div, curr;
	long long k, b;
	bool flag;
	scanf("%d", &T);
	T = T << 1;
	for(int ix = 0; ix != T; ix += 2)
		scanf("%d", arr + ix);
	for(a = 0; a <= 10000; ++a){
		c = arr[2] - a * a * arr[0];
		div = gcd(10001, a+1);
		if(c % div) continue;
		exgcd(10001, a+1, k, b);
		b = b * (c / div);
		b = (b % 10001 + 10001) % 10001;
		printf("a = %d, b = %d\n", a, b);

		flag = true;
		for(int ix = 1; ix != T; ++ix){
			curr = (a * arr[ix-1] + b) % 10001;
			if(ix & 1) arr[ix] = curr;
			else
			if(arr[ix] != curr){
				flag = false;
				break;
			}else
			printf("curr: %d\n", curr);
		}
		//cin.ignore();
		if(flag) break;
	}
	for(int ix = 1; ix < T; ix += 2)
		printf("%d\n", arr[ix]);
	return 0;
}
