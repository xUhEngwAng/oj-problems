#include <cstdio>
#include <string>
using namespace std;

/*
 * 这个题我是完全不会做，就连 n = 2 的情形都用幂级数推导了半天
 * 才得到答案是 3......我发觉我的思路比较古板啊，就一直在想用
 * 期望的定义，因此想要求出抽 k 次才抽到完整的 n 张卡片的概率。
 * 关于这个概率，我想出了一种 dp 的方案，但是求期望是要计算
 * 无穷级数啊，遂放弃......
 *
 * 看紫书的解法，是说当前手里有 k 张不同的卡片，则平均要抽
 * 1- k / n 次才能得到一张新的卡片。将上述式子从 k = 0 累加到
 * k = n - 1 即可。于是我就手写了一个分数运算，仅此而已。
 *
 * 这种问题我感觉完全是数学题啊，就只有能做出这道题，编码倒是
 * 相对容易的。没想到我一个准研究生连高中生数学都不会做......
 */

struct fraction{
	long long up, down;
};

fraction ans[34], temp;

long long gcd(long long a, long long b){
	if(b == 0) return a;
	return gcd(b, a % b);
}

fraction add(const fraction &one, const fraction &two){
	fraction ret;
	ret.down = one.down * two.down;
	ret.up   = one.up * two.down + two.up * one.down;
	long long g = gcd(ret.down, ret.up);
	ret.down = ret.down / g;
	ret.up   = ret.up / g;
	return ret;
}

void init(){
	long long g;
	ans[1].up = ans[1].down = 1;
	temp.up = 1;
	for(int ix = 2; ix <= 33; ++ix){
		temp.down = ix;
		ans[ix] = add(ans[ix-1], temp);
	}
	for(int ix = 2; ix <= 33; ++ix){
		ans[ix].up = ans[ix].up * ix;
		g = gcd(ans[ix].down, ans[ix].up);
		ans[ix].down = ans[ix].down / g;
		ans[ix].up   = ans[ix].up / g;
	}
}

void print(fraction frac){
	int integer = frac.up / frac.down;
	string str;
	frac.up = frac.up - integer * frac.down;
	if(frac.up == 0) printf("%d", integer);
	else{
		str = to_string(integer);
		for(int ix = 0; ix <= str.size(); ++ix) printf(" ");
		printf("%lld\n", frac.up);
		printf("%d ", integer);
		str = to_string(frac.down);
		for(int ix = 0; ix != str.size(); ++ix) printf("-");
		printf("\n");
		str = to_string(integer);
		for(int ix = 0; ix <= str.size(); ++ix) printf(" ");
		printf("%lld", frac.down);
	}
}

int main(){
	init();
	int n;
	while(scanf("%d", &n) == 1){
		print(ans[n]);
		printf("\n");
	}
	return 0;
}
