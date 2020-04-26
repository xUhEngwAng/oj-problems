#define VERSION2

#ifdef  VERSION1
#include <cstdio>

struct matrix{
	int x, y, z, w;
	matrix(int one, int two, int three, int four): x(one), y(two), z(three), w(four){}
	matrix() = default;
};

void mod(matrix &input, int p){
	input.x = input.x % p;
	input.y = input.y % p;
	input.z = input.z % p;
	input.w = input.w % p;
}

matrix multiply(const matrix &left, const matrix &right){
	matrix ret;
	ret.x = left.x * right.x + left.y * right.z;
	ret.y = left.x * right.y + left.y * right.w;
	ret.z = left.z * right.x + left.w * right.z;
	ret.w = left.z * right.y + left.w * right.w;
	return ret;
}

matrix pow(const matrix &base, long long exp, int p){
	matrix ret(1, 0, 0, 1);
	matrix power = base;
	while(exp){
		if(exp & 1){
			ret = multiply(ret, power);
			mod(ret, p);
		}
		power = multiply(power, power);
		mod(power, p);
		exp = exp >> 1;
	}
	return ret;
}

int compute(long long a, long long b, int n){
	matrix unit(0, 1, 1, 1);
	matrix res = pow(unit, a, n);
	res = pow(res, b, n);
	return res.y;
}

int main(){
	int t, n, res;
	long long a, b;
	scanf("%d", &t);
	while(t--){
		scanf("%lld %lld %d", &a, &b, &n);
		res = compute(a, b, n);
		printf("%d\n", res);
	}
}

#else//VERSION2

#include <iostream>
using namespace std;

int arr[1000005];

int compute(int n){
	arr[0] = 0;
	arr[1] = 1 % n;
	if(n == 1) return 1;
	int len = 2;
	for(int ix = 2; ; ++ix){
		arr[ix] = (arr[ix - 2] + arr[ix - 1]) % n;
		if(arr[ix] == 1 && arr[ix - 1] == 0) return ix - 1;
	}
}

int pow(unsigned long long a, unsigned long long b, int period){
	int ret = 1;
	int pow = a % period;
	while(b){
		if(b & 1) ret = (ret * pow) % period;
		pow = (pow * pow) % period;
		b = b >> 1;
	}
	return ret;
}

int main(){
	int t, n, pos, period;
	unsigned long long a, b;
	cin >> t;
	while(t--){
		cin >> a >> b >> n;
		period = compute(n);
		pos = pow(a, b, period);
		cout << arr[pos] << endl;
	}
	return 0;
}

#endif
