#include <vector>
#define MAX(X, Y) ((X)<(Y)?(Y):(X))
using std::vector;

/*
 * 这个题在面试阿里的时候遇到，我居然没有想出背包解......
 * 按理说这么熟悉的题，上课也讲过，以前也写过，还是我太菜了
 * 吧。另外，01 背包的时间复杂度优化我也不是很熟，写了一会儿。
 */

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int target = 0, n = nums.size();
        for(auto num : nums){
            target += num;
        }
        if(target & 1) return false;
        target = target >> 1;

        vector<int> dp(target+1, 0);
        
        for(int ix = 0; ix != n; ++ix){
            for(int jx = target; jx >= 0; --jx){
                if(jx < nums[ix]) continue;
                dp[jx] = MAX(dp[jx], dp[jx-nums[ix]] + nums[ix]);
            }
        }

        return dp[target] == target;
    }
};
