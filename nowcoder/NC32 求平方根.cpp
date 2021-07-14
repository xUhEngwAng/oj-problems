class Solution {
public:
    /**
     * 
     * @param x int整型 
     * @return int整型
     */
    int sqrt(int x) {
        // write code here
        if(x <= 0) return 0;
        long long lo = 0, hi = x + 1, mid, square;
        while(lo < hi){
            mid = (lo + hi) >> 1;
            square = mid * mid;
            if(x < square) hi = mid;
            else if (square < x) lo = mid + 1;
            else return mid;
        }
        return lo-1;
    }
};
