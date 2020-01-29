#include <cstdio>
#include <cstdlib>

/*
 * 这个题做了好久好久，我感觉自己的代码是完美的，但是就是两个
 * 测试点过不了，后来发现是在一些细节上存在问题。
 * 
 * 1. 输出格式的问题。这个也许是我的理解不够到位吧，但是题目
 *    上确实没有说明清楚。对于负的假分数，如 -2/3，我是理解为
 *    输出 -1 -1/2，然而实际应该输出 -1 1/2，也就是完全按照
 *    假分数的形式进行输出。此时应该有
 *
 *    if(abs(res_numeritor) >= res_denomitor):
 *        integral = res_numeritor / res_denomitor
 *        res_numeritor = res_numeritor % res_denomitor
 *    else:
 *        integral = 0
 *
 * 2. 数据范围的问题。我所有数据几乎都用的是 long long，想的是
 *    应该不可能爆范围了吧，结果还是爆了。问题出在分子累加的循
 *    环。我写的是
 *
 *    res_numeritor += numeritor[ix] * 
 *                     res_denomitor / denomitor[ix];
 *
 *    但是 numeritor[ix] * res_denomitor 可能就爆了 long long
 *    了，毕竟 res_denomitor 可能很大。改成
 *
 *    res_numeritor += numerator[ix] *
 *                     (res_denomitor / denominator[ix]);
 *
 *    就 AC 了。
 */

void swap(long long &one, long long &two){
	long long tmp = one;
	one = two;
	two = tmp;
}

long long gcd(long long one, long long two){
    if(one == 0 || two == 0) return 0;
    if(one < 0) one = -one;
    if(two < 0) two = -two;
	long long res = 1, tmp;
	while(true){
		if(one < two) swap(one, two);
		while(!(one & 1) && !(two & 1)){
			one = one >> 1;
			two = two >> 1;
			res = res << 1;
		}
		tmp = one - two;
		if(tmp == 0){
			res = two * res;
			break;
		}
		one = tmp;
	}
	return res;
}

int main(){
	int N;
	scanf("%d", &N);
	long long *numerator = new long long[N];
	long long *denominator = new long long[N];
	for(int ix = 0; ix != N; ++ix)
		scanf("%lld/%lld", numerator + ix, denominator + ix);

	long long res_denomitor = denominator[0];
	for(int ix = 1; ix != N; ++ix){
		res_denomitor *= denominator[ix] /
		gcd(denominator[ix - 1], denominator[ix]);
	}
	long long res_numeritor = 0;
	for(int ix = 0; ix != N; ++ix)
		res_numeritor += numerator[ix] *
		(res_denomitor / denominator[ix]);

	long long devisor = gcd(res_numeritor, res_denomitor);
	if(devisor != 0){
	    res_numeritor /= devisor;
	    res_denomitor /= devisor;
	}

	int integral = 0;
	if(abs(res_numeritor) >= res_denomitor){
	    integral = res_numeritor / res_denomitor;
		res_numeritor = abs(res_numeritor) % res_denomitor;
	}
	if(integral != 0){
		printf("%d", integral);
		if(res_numeritor != 0)
			printf(" %lld/%lld\n", res_numeritor, res_denomitor);
	}else{
		if(res_numeritor != 0)
			printf("%lld/%lld\n", res_numeritor, res_denomitor);
		else
			printf("0\n");
	}
	return 0;
}
