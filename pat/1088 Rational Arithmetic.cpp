#include <cstdlib>
#include <cstdio>
#include <algorithm>
using namespace std;

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
	Fraction(long long u, long long d): up(u), down(d){
		simplify();
	}

	void simplify(){
		long long devisor = gcd(abs(up), down);
		if(devisor != 0){
			up = up / devisor;
			down = down / devisor;
		}
		if(up == 0 && down != 0)
			down = 1;
	}

	void print() const {
		if(down == 0){
			printf("Inf");
			return;
		}
		if(up < 0) printf("(");
		long long integral = 0;
		long long u = up;
		if(abs(up) >= down){
			integral = up / down;
			u = abs(up) % down;
		}
		if(integral != 0){
			printf("%lld", integral);
			if(u != 0)
				printf(" %lld/%lld", u, down);
		}else{
			if(u != 0) printf("%lld/%lld", u, down);
			else printf("0");
		}
		if(up < 0) printf(")");
	}

	Fraction add(const Fraction& right){
		Fraction res;
		res.down = down * (right.down / gcd(down, right.down));
		res.up = up * (res.down / down) + right.up * (res.down / right.down);
		res.simplify();
		return res;
	}

	Fraction subtract(const Fraction& right){
		Fraction res;
		res.down = down * (right.down / gcd(down, right.down));
		res.up = up * (res.down / down) - right.up * (res.down / right.down);
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
	printRes(one, two, '+');
	printRes(one, two, '-');
	printRes(one, two, '*');
	printRes(one, two, '/');
	return 0;
}
