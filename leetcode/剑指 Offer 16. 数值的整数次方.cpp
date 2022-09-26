#include <iostream>
using namespace std;

/*
 * 这个题无非是一个快速幂，但我被数字范围折磨了一会儿。这里n可以取
 * [-2^31, 2^31-1]，当 n = -2^31 时，-n 超出了int的范围。本来我的
 * 想法是 fast_pow 的输入为 long long 类型的 n，因此就可以做隐式类
 * 型转换，从而规避这一问题。然而在计算 -n 时，c++ 还是保持了 int
 * 的类型，此时 -n 的值是多少就是我的知识盲区了。要完成了 -n 的计算，
 * 才会进行隐式类型转换。从而上述做法就出错了。
 *
 * 正确的做法是，先把 n 转换为 long long，然后再计算 -n。
 */

class Solution {
public:
    double myPow(double x, int n) {
        if(n < 0) return 1 / fast_pow(x, -(long long)n);
        else return fast_pow(x, n);
    }

    double fast_pow(double x, long long n){
        double ret = 1.0, prod = x;

        while(n){
            if(n & 1) ret *= prod;
            prod = prod * prod;
            n = n >> 1;
        }

        return ret;
    }
};

int main(){
    double x;
    int n;
    Solution solution;
    
    while(cin >> x >> n){
        double res = solution.myPow(x, n);
        cout << "The result is " << res << "." << endl;
    }

    return 0;
}
