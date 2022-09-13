/*
 * 小红书面试问到了原题，yet 我之前没写过，从零开始思考的。
 * 确实也想到了用动态规划，dp 数组的定义和题解也一模一样，
 * 但是状态转移方程写的不好，是将 s 和 t 一个位置一个位置
 * 进行对齐，因此时间复杂度应该是 O(m^2 * n)。
 *
 * 实际上这个题的状态转移方程和 0-1 背包问题几乎完全相同，
 * 也可以使用同样的办法对空间进行优化，但边界情况需要好好
 * 分析，细节还是比较多的。另外 leetcode 上给的 case 似乎
 * 是有问题的。
 */

class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.length(), n = t.length();
        vector<int> dp(n+1, 0);
        if(s.back() == t.back()) dp[n-1] = 1;
        dp[n] = 1;

        for(int ix = m - 2; ix >= 0; --ix){
            for(int jx = 0; jx != n; ++jx){
                if(s[ix] == t[jx])
                    dp[jx] += dp[jx+1];
            }
        }

        return dp[0];
    }
};
