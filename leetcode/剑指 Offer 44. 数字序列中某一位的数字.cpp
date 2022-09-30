#include <string>
#include <cmath>
using namespace std;

class Solution {
public:
    int findNthDigit(int n) {
        int len = 2, num_digit = 90;
        if(n < 10) return n;
        n -= 10;

        while(true){
            if(n < (long long)len * num_digit) break;
            n = n - len * num_digit;
            len += 1;
            num_digit *= 10;
        }

        int shift = n / len, bias = n % len;
        return to_string(pow(10, len-1) + shift)[bias] - '0';
    }
};
