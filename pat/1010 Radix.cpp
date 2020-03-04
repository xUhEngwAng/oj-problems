#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

/*
 * 这个题觉得难度真的爆炸！看《算法笔记》还有网上的题解，无一
 * 例外几乎都是用 long long 加二分查找。我寻思这题也没说转化
 * 成十进制以后就不会超过 long long 吧，只能说明 PAT 的数据
 * 确实垃圾，大家这样做题确实是不严谨的，给人的感觉是看了答案
 * 之后再做的。不管怎么样，我还是写了个非常严谨的算法，可以处
 * 理任意大的数字。
 *
 * 此题首先需要明确，radix 的范围并不局限于 2 ~ 36，而可以是
 * 任意的整数，我一开始就是犯了这个错误......这样一来，十位的
 * N1 和 N2 也非常容易超出 long long 的范围，因此要手写大数
 * 的运算。我这里主要是实现了大数的乘法，其实是比较粗糙，是把
 * 多位数的乘法多分多个一位数的乘法，然后每个一位数的乘法都是
 * 通过大数加法来实现的，性能可能多少会差一些。直接用乘法法则
 * 实现一位数乘法也是可行的。
 *
 * 有了大数的加法和乘法，就可以根据 radix 将 N1 和 N2 转换成
 * 十进制整数了。此后只需要遍历 radix，判断 decimal1 和 decimal2
 * 是否相同，就可以找到另一个数字对应的 radix 了——这也是我一
 * 开始的策略，然而 radix 的上界确实太大，逐个遍历的话时间开销
 * 太大，会有一个测试点超时。因此需要使用二分查找。
 *
 * 首先需要明确二分查找的上界和下界，下界应该可以由输入 N1 或
 * N2 来直接确定，即 最大数字 + 1。而上界则是另一个数字的十进制
 * 表示 + 1，不妨记为 decimal + 1。如果 N2 有不少于两个数位，
 * 则 decimal2 >= decimal1 + 1，可见 decimal1 + 1确实构成
 * 上界。如果 N2 只有一个数位，则无论进制是多少，decimal2 都
 * 是不变的。这个也是困扰我很久的一个问题。
 *
 * 为了实现二分查找，还要首先实现大数的除以二的运算，这里我又
 * 手写了除法运算，还好只是除以二，难度可以接受。
 *
 * 我还犯的一个错误，是忽略了可能存在多个进制，使得两个数字相同，
 * 根据题意，此时应该选择其中的最小者。因此这里的二分查找需要是
 * 邓公所说的第三个版本，只不过是将等于和大于的情况合并而已。
 */

//m, n serve as BIG-END decimal integers
string add(const string &m, const string &n){
    string res;
    int carry = 0, mlen, nlen, one, two, curr;
    mlen = m.length();
    nlen = n.length();
    for(int ix = mlen - 1, jx = nlen - 1; ix >= 0 || jx >= 0; --ix, --jx){
        one = (ix >= 0? m[ix] - '0': 0);
        two = (jx >= 0? n[jx] - '0': 0);
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

string multiply_onedigit(const string &m, int count){
	//assert(0 <= count < 10);
    string res;
    while(count--){
        res = add(res, m);
    }
    return res;
}

string multiply(const string &m, const string &n){
    string res, curr;
    int ix = 0;
	for (auto it = n.rbegin(); it != n.rend(); ++it) {
        curr = multiply_onedigit(m, *it - '0');
        for(int jx = 0; jx < ix; ++jx)
            curr.push_back('0');
        res = add(res, curr);
        ++ix;
    }
    return res;
}

string countDecimal(const string &n, const string &radix){
    string pow = "1";
    string res;
    int digit;
    for(auto it = n.rbegin(); it != n.rend(); ++it){
        if(*it <= '9') digit = *it - '0';
        else           digit = *it - 'a' + 10;
        res = add(res, multiply(pow, to_string(digit)));
        pow = multiply(pow, radix);
    }
    return res;
}

int cmp(const string &one, const string &two){
    if(one.size() == two.size()){
        if(one < two)  return -1;
        if(one > two)  return 1;
        if(one == two) return 0;
    }
    if(one.size() < two.size())
        return -1;
    return 1;
}

string half(const string &str){
    string res;
    int up, remain, ix = 0;
    up = str.front() - '0';
    if(up < 2 && str.size() >= 2){
        up *= 10;
        up += str[1] - '0';
        ++ix;
    }
   while(true){
        res.push_back((up >> 1) + '0');
        remain = up & 1;
        if(++ix >= str.size()) break;
        up = remain * 10 + str[ix] - '0';
    }
    return res;
}

int main(){
    string N1, N2, radix;
    int tag;
    cin >> N1 >> N2 >> tag >> radix;

    if(tag == 2) swap(N1, N2);
    string decimal1 = countDecimal(N1, radix);
    int leastRadix = 2, digit;
    for(char ch : N2){
        if(ch <= '9') digit = ch - '0';
        else          digit = ch - 'a' + 10;
        if(leastRadix <= digit) leastRadix = digit + 1;
    }

    string lo = to_string(leastRadix), hi = add(decimal1, "1");
    string decimal2, mid;
    while(cmp(lo, hi) == -1){
        mid = half(add(lo, hi));
        decimal2 = countDecimal(N2, mid);
        if(cmp(decimal1, decimal2) == 1) lo = add(mid, "1");
        else hi = mid;
    }
    decimal2 = countDecimal(N2, lo);
    if(decimal1 == decimal2) cout << lo << endl;
    else cout << "Impossible" << endl;
    return 0;
}
