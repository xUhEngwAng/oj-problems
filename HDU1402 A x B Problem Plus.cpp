#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;
#define maxn (1 << 17)

struct complex{
	double real = 0, imag = 0;
	complex() = default;
	complex(double r, double i): real(r), imag(i){}
	complex operator*(const complex &right){
		complex ret;
		ret.real = real * right.real - imag * right.imag;
		ret.imag = real * right.imag + imag * right.real;
		return ret;
	}
	complex operator+(const complex &right){
		return complex(real + right.real, imag + right.imag);
	}
	complex operator-(const complex &right){
		return complex(real - right.real, imag - right.imag);
	}
};

complex wn[maxn], wn_minus[maxn];
complex a[maxn], b[maxn];

void init(int n){
	double pi = acos(-1);
	for(int ix = 0; ix != n; ++ix){
		wn[ix].real = cos(2 * pi * ix / n);
		wn[ix].imag = sin(2 * pi * ix / n);
		wn_minus[ix].real = wn[ix].real;
		wn_minus[ix].imag = -wn[ix].imag;
	}
}

void fft(complex *a, int n, int op){
	for(int ix = 0, jx = 0; ix != n; ++ix){
		if(ix > jx) swap(a[ix], a[jx]);
		for(int l = n >> 1; (jx = jx ^ l) < l; l = l >> 1);
	}
	int m;
	complex z;
	for(int ix = 2; ix <= n; ix = ix << 1){
		m = ix >> 1;
		for(int jx = 0; jx != n; jx += ix)
			for(int kx = 0; kx != m; ++kx){
				if(op) z = wn[kx * n / ix] * a[jx + kx + m];
				else   z = wn_minus[kx * n / ix] * a[jx + kx + m];
				a[jx + kx + m] = a[jx + kx] - z;
				a[jx + kx] = a[jx + kx] + z;
			}
	}
	if(!op)
		for(int ix = 0; ix != n; ++ix){
			a[ix].real = a[ix].real / n;
			a[ix].imag = a[ix].imag / n;
		}
}

int main(){
	string one, two;
	int len, m, n;
	while(cin >> one >> two){
		len = 1;
		m = one.size(), n = two.size();
		while(len < m + n) len = len << 1;
		memset(a, 0, len * sizeof(complex));
		memset(b, 0, len * sizeof(complex));
		for(int ix = 0; ix != m; ++ix)
			a[ix].real = one[m - 1- ix] - '0';
		for(int ix = 0; ix != n; ++ix)
			b[ix].real = two[n - 1- ix] - '0';
		init(len);
		fft(a, len, 1);
		fft(b, len, 1);
		for(int ix = 0; ix != len; ++ix)
			a[ix] = a[ix] * b[ix];
		fft(a, len, 0);
		for(int ix = 0; ix != len; ++ix)
			cout << a[ix].real << endl;
		string res;
		int carry = 0, curr;
		for(int ix = 0; ix != len; ++ix){
			curr = a[ix].real + carry + 0.5;
			carry = curr / 10;
			curr = curr - 10 * carry;
			res.push_back(curr + '0');
		}
		if(carry) res.push_back(carry + '0');
		while(res.back() == '0') res.pop_back();
		reverse(res.begin(), res.end());
		if(!res.empty()) cout << res << endl;
		else cout << "0" <<endl;
	}
	return 0;
}
