#define MOD (1000000007)

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param n int 被划分的数
     * @param k int 化成k份
     * @return int
     */
    int divideNumber(int n, int k) {
        // write code here
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
        dp[0][0] = 1;
        for(int ix = 1; ix <= n; ++ix){
            for(int jx = 1; jx <= ix && jx <= k; ++jx){
                dp[ix][jx] = (dp[ix-1][jx-1] + dp[ix-jx][jx]) % MOD;
            }
        }
        return dp[n][k];
    }
};
