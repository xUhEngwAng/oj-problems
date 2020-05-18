#include <cstdio>
#include <cmath>
#include <iostream>
using std::cin;

double compute(int n, double p){
	double one, two, temp = 0.0, ret;
	one = (n+1) * log(p);
	two = (n+1) * log(1-p);
	ret = n * (exp(one) + exp(two));
	for(int k = n - 1; k > 0; --k){
		temp = temp + log(2*n-k) - log(n-k);
		one = temp + (n+1) * log(p) + (n-k) * log(1-p);
		two = temp + (n+1) * log(1-p) + (n-k)* log(p);
		ret += k * (exp(one) + exp(two));
	}
	return ret;
}

int main(){
	int n, cnt = 1;
	double p;
	while(scanf("%d %lf", &n, &p) == 2){
		printf("Case %d: ", cnt++);
		printf("%.6f\n", compute(n, p));
	}
	return 0;
}
