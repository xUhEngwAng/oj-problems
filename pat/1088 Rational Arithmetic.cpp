#include <cstdlib>
#include <cstdio>
#include <algorithm>
using namespace std;

/*
 * 这个题我感觉难度还是有的，主要倒不在于思维逻辑比较复杂，
 * 而是控制逻辑比较复杂，比如说数字的打印，就要考虑不少情况：
 * 分子为零，分母为零，整数部分为零，小数部分为零，还是很有
 * 意思的一个题。
 *
 * 我的问题主要有两点，首先是 gcd 的实现，我本来用更相减损术，
 * 因为邓公说更相减损术的性能更优，结果我一跑简直慢成马了。才
 * 赶紧换了辗转相除法。更相减损太慢主要是存在极端输入，比如
 * a = 100,000, b = 1 这种，那肯定超级慢啊。
 *
 * 另外一方面是我蠢了，本来我的 Fraction 类的构造函数最后调用
 * 了 simplify 来进行化简。然而我输入的方法根本没让它有机会
 * 调用构造函数啊，我是直接把值输入到两个对象中。这样对于一些
 * 可以化简的分式，比如 5000/10000 我的程序直接就把这个原始值
 * 输出了，而不是化简之后的结果。
 */

long long gcd(long long one, long long two){
	if(one == 0 || two == 0) return 0;
	long long res = 1, tmp;
	while(true){
        if(one < two) swap(one, two);
		tmp = one % two;
        if(tmp == 0){
            res = two;
            break;
        }
        one = tmp;
	}
	return res;
}

class Fraction{
public:
	long long up, down;

	Fraction(): up(0), down(1){}

	void simplify(){
		long long devisor = gcd(abs(up), down);
		if(devisor != 0){
			up = up / devisor;
			down = down / devisor;
		}
	}

	void print() const {
		if(down == 0){
			printf("Inf");
			return;
		}
		if(up == 0){
			printf("0");
			return;
		}
		if(up < 0) printf("(-");
		long long integral = abs(up) / down;
		long long u = abs(up) % down;
		if(integral != 0) printf("%lld", integral);
		if(integral != 0 && u != 0) printf(" ");
		if(u != 0) printf("%lld/%lld", u, down);
		if(up < 0) printf(")");
	}

	Fraction add(const Fraction& right){
		Fraction res;
		res.down = down * right.down;
		res.up = up * right.down + right.up * down;
		res.simplify();
		return res;
	}

	Fraction subtract(const Fraction& right){
		Fraction res;
		res.down = down * right.down;
		res.up = up * right.down - right.up * down;
		res.simplify();
		return res;
	}

	Fraction multiply(const Fraction& right){
		Fraction res;
		res.up = up * right.up;
		res.down = down * right.down;
		res.simplify();
		return res;
	}

	Fraction divide(const Fraction& right){
		Fraction res;
		res.up = up * right.down;
		res.down = down * right.up;
		if(res.down < 0){
			res.down *= -1;
			res.up *= -1;
		}
		res.simplify();
		return res;
	}
};

void printRes(Fraction one, Fraction two, char op){
	Fraction res;
	one.print();
	if(op == '+'){
		printf(" + ");
		res = one.add(two);
	}
	else if(op == '-'){
		printf(" - ");
		res = one.subtract(two);
	}
	else if(op == '*') {
		printf(" * ");
		res = one.multiply(two);
	}
	else{
		printf(" / ");
		res = one.divide(two);
	}
	two.print();
	printf(" = ");
	res.print();
	printf("\n");
}

int main(){
	Fraction one, two;
	scanf("%lld/%lld %lld/%lld", &one.up, &one.down, &two.up, &two.down);
	one.simplify();
	two.simplify();
	printRes(one, two, '+');
	printRes(one, two, '-');
	printRes(one, two, '*');
	printRes(one, two, '/');
	return 0;
}
