class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        // super clever solution
        int one = 0x7fffffff, two = 0x7fffffff;
        
        for(int ix = 0; ix != nums.size(); ++ix){
            if(two < nums[ix]) return true;
            if(one < nums[ix]) two = nums[ix];
            else               one = nums[ix];
        }

        return false;

        // naive LIS solution, O(n^2) and O(n)
        /*
        vector<int> dp;
        dp.resize(nums.size(), 1);
        
        for(int ix = 0, jx; ix != nums.size(); ++ix){
            for(jx = ix - 1; jx >= 0; --jx){
                if(nums[jx] < nums[ix] && dp[ix] < dp[jx] + 1)
                    dp[ix] = dp[jx] + 1;
            }
            if(dp[ix] >= 3) return true;
        }

        return false;
        */
    }
};