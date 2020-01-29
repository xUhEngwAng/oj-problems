#include <cstdio>

/*
 * 这么简单一个题我居然没有 AC，结果原来是一个C语言的小问题。
 * 我此前写的是
 *
 * res += (N - ix) * (ix + 1) * arr[ix];
 *
 * 由于 N 和 ix 都是 int 型的，这样 (N - ix)*(ix + 1)可能会
 * 爆了 int 了，把两者都改成 long long 就可以了。另一种方法是
 * 
 * res += arr[ix] * (N - ix) * (ix + 1);
 * 
 * 由于 arr[ix] 是 double 类型的，就不会溢出了。
 */

int main(){
	long long N;
	scanf("%lld", &N);
	double *arr = new double[N];
	for(int ix = 0; ix != N; ++ix)
		scanf("%lf", arr + ix);
	double res = 0.0;
	for(long long ix = 0; ix != N; ++ix)
		res += (N - ix) * (ix + 1) * arr[ix];
    printf("%.2lf\n", res);
	return 0;
}
