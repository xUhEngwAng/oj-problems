#include <algorithm>
#include <iostream>
#include <string>

#define NEWVERSION
//#define OLDVERSION

using namespace std;

void swap(string &str1, string &str2){
    string temp = str1;
    str1 = str2;
    str2 = temp;
}

//m, n serve as BIG-END decimal integers
string add(string m, string n){
    string res;
    int carry = 0, mlen, nlen, one, two, curr;
    mlen = m.length();
    nlen = n.length();
    for(int ix = m - 1, jx = n - 1; ix >= 0 || jx >= 0; --ix, --jx){
        one = (ix >= 0? m[ix] - '0': 0);
        two = (jx >= 0? n[ix] - '0': 0);
        curr = one + two + carry;
        if(curr >= 10){
            curr -= 10;
            carry = 1;
        }else{carry = 0;}
        res.push_back(curr + '0');
    }
    if(carry) res.push_back('1');
    reverse(res.begin(), res.end());
    return res;
}

string multiply_onedigit(string m, int count){
    string res;
    while(count--){
        res = add(res, m);
    }
    return res;
}

string multiply(string m, string n){
    string res, curr;
    int ix = 0;
    for(char ch : n){
        curr = multiply_onedigit(m, ch - '0');
        for(int jx = 0; jx < ix; ++jx)
            curr.push_back('0');
        res = add(res, curr);
        ++ix;
    }
    return res;
}

string int2str(int n){
    string res;
    while(n != 0){
        res.push_back(n % 10 + '0');
        n = n / 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

#ifdef NEWVERSION

string countDecimal(string n, int radix){
    string pow = "1";
    string res, radixStr = int2str(radix);
    int digit;
    for(auto it = n.rbegin(); it != n.rend(); ++it){
        if(*it <= '9') digit = *it - '0';
        else           digit = *it - 'a' + 10;
        res = add(res, multiply(pow, int2str(digit)));
        pow = multiply(pow, radixStr);
    }
    return res;
}

#else
long long countDecimal(string N, int radix){
    long long res = 0, pow = 1;
    int digit;
    for(auto it = N.rbegin(); it != N.rend(); ++it){
        if(*it <= '9') digit = *it - '0';
        else           digit = *it - 'a' + 10;
        res += digit * pow;
        pow *= radix;
    }
    return res;
}
#endif // NEWVERSION

int main(){
    string N1, N2;
    int tag, radix;
    cin >> N1 >> N2 >> tag >> radix;

    if(tag == 2) swap(N1, N2);
    string decimal1 = countDecimal(N1, radix);
    int leastRadix = 2, digit;
    for(char ch : N2){
        if(ch <= '9') digit = ch - '0';
        else          digit = ch - 'a' + 10;
        if(leastRadix <= digit) leastRadix = digit + 1;
    }

    int ix;
    string decimal2;
    for(ix = leastRadix; ; ++ix){
        decimal2 = countDecimal(N2, ix);
        if(decimal2 == decimal1){
            cout << ix << endl;
            break;
        }
        if(decimal2 > decimal1){
            cout << "Impossible" << endl;
            break;
        }
    }
    return 0;
}
