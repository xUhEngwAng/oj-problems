class Solution {
public:
    int countDigitOne(int n) {
        int ret = 0;
        long long tmp = 10;
        int left, right, curr;

        while(true){
            left = n / tmp;
            right = n % tmp;
            curr = right / (tmp / 10);
            right = right % (tmp / 10);
            if(curr == 0 && left == 0) break;

            if(curr < 1) ret += left * tmp / 10;
            else if(curr == 1) ret += left * tmp / 10 + right + 1;
            else ret += (left + 1) * tmp / 10;

            tmp *= 10;
        }

        return ret;
    }
};
