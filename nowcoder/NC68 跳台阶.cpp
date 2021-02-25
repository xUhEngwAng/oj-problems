class Solution {
public:
    int jumpFloor(int number) {
        vector<int> dp;
        dp.reserve(number + 1);
        dp.push_back(1);
        dp.push_back(1);
        
        for(int i = 2; i <= number; ++i)
            dp[i] = dp[i - 1] + dp[i - 2];
        
        return dp[number];
    }
};