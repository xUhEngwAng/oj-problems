#include <cstdio>
#define P    (1000000007)
#define MAXN (1000000001)

int b[101], n, m, a;

long long fcn(int k){
	long long ret = 0;
	long long pow = 1;
	for(int ix = 0; ix <= m; ++ix){
		ret += (pow * b[ix]) % P;
		pow = (pow * k) % P;
	}
	return ret % P;
}

int main(){
	scanf("%d %d %d", &n, &m, &a);
	for(int ix = 0; ix <= m; ++ix)
		scanf("%d", b + ix);
	long long pow = 1, res = 0, fk;
	for(int ix = 0; ix <= n; ++ix){
		fk = fcn(ix);
		res += (pow * fk) % P;
		pow = (pow * a) % P;
		if(res >= P) res = res % P;
	}
	printf("%d\n", res);
	return 0;
}
