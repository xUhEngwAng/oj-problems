#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

//这个题我此前的思路是有问题的，我以为用long long应该就不会爆int了，
//但是实际上，最坏情况下每一次迭代输入的N都可能翻倍（甚至翻10倍，
//所以long long的字长也是不够的。所以这个题要自己写大数加法。
//一开始的错误思路的代码在最下面。
#define NEWVERSION
//#define OLDVERSION

#ifdef NEWVERSION

string add(string one, string two){
    string res;
    int carry = 0, m, n;
    int i, j, digit, first, second, len = 0;
    m = one.length();
    n = two.length();
    for(i = m - 1, j = n - 1; i >= 0 || j >= 0; --i, --j, ++len){
        first = (i < 0? 0: one[i] - '0');
        second = (j < 0? 0: two[j] - '0');
        digit = first + second + carry;
        if(digit < 10) {carry = 0;}
        else           {carry = 1; digit -= 10;}
        res.push_back(digit + '0');
    }
    if(carry){
        res.push_back('1');
    }
	reverse(res.begin(), res.end());
	return res;
}

int main(){
    string N, reve;
    int K, ix;
    cin >> N >> K;
    for(ix = 0; ix != K; ++ix){
		reve = N;
        reverse(reve.begin(), reve.end());
        if(reve == N) break;
        N = add(N, reve);
    }
    cout << N << endl;
    cout << ix;
    return 0;
}

#else
long long reverse(long long n){//reverse number n in decimal digits
    int digit;
    long long res = 0;
    while(n != 0){
        res = res * 10;
        digit = n % 10;
        res += digit;
        n = n / 10;
    }
    return res;
}

int main(){
    int K, ix = 0;
    long long N;
    scanf("%lld %d", &N, &K);

    long long reve;
    while(K-- != 0){
        reve = reverse(N);
        if(N == reve) break;
        //else
        N += reve;
        ++ix;
    }
    printf("%lld\n", N);
    printf("%d", ix);
    return 0;
}

#endif // NEWVERSION
