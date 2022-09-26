class Solution {
public:
    int consecutiveNumbersSum(int n) {
        int k = 1, minSum, ret = 0;

        while(true){
            minSum = (k+1)*k/2;
            if(n < minSum) break;
            ret += checkConsecutive(n, k);
            ++k;
        }

        return ret;
    }

    int checkConsecutive(int n, int k){
        /*
         * (2n - k(k-1))/(2k) is a digit <=> 
         * n can be the sum of k consecutive positive inteegerss
         */
        int numerator = n*2 - k*(k-1);
        if(numerator % (k << 1)) return 0;
        return 1;
    }
};
