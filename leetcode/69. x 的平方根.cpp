class Solution {
public:
    int mySqrt(int x) {
        if(x <= 1) return x;

        int begin = 0, end = x;
        long long mid, sqr;

        while(begin < end){
            mid = (begin + end) >> 1;
            sqr = mid * mid;
            if(sqr < x) begin = mid + 1;
            else if(x < sqr) end = mid;
            else return mid;
        }

        return begin - 1;
    }
};
