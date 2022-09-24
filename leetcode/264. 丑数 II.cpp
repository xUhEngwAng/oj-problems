/*
 * 这个题我想了好久始终没有想到比较好的解法。这里的想法是维护到
 * 目前为止的所有丑数，而所有这些数乘以 2, 3, 5 也还是丑数。因此
 * 我们只需要保存还没有乘 2, 3, 5 的第一个数，他们后面的数也必然
 * 还没有乘以 2, 3, 5。这样，这些数字的 2/3/5 倍乘积的最小值就是
 * 下一个丑数。
 */

#define MIN(X, Y) ((X)<(Y)?(X):(Y))

class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> dp(1, 1);
        dp.reserve(n);
        int p2 = 0, p3 = 0, p5 = 0, curr;

        while(dp.size() < n){
            curr = MIN(dp[p5] * 5, MIN(dp[p2] * 2, dp[p3] * 3));
            if(curr == dp[p2] * 2) p2 += 1;
            if(curr == dp[p3] * 3) p3 += 1;
            if(curr == dp[p5] * 5) p5 += 1;
            dp.push_back(curr);
        }

        return dp.back();
    }
};
