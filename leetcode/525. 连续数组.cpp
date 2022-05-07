#include <vector>
#include <unordered_map>
using namespace std;

/*
 * again 没有写出最优解。我的思路首先是做两重循环，遍历
 * 每个起点与终点，复杂度为 O(n^2)。然后在这个 naive 解
 * 法的基础上优化。使用 dp[i] 表示以位置 i 结尾的最长子
 * 数组，对于 dp[i+1]，如果 nums[i+1] != nums[i-dp[i]]，
 * 则直接更新 dp[i+1] = dp[i] + 2 + dp[i-dp[i]-1]，否则
 * 则需要从 i+1 开始做一次遍历。虽则这个方法对 naive 的
 * 解法进行了优化，但最坏情况下时间复杂度仍然为 O(n^2)。
 *
 * 结果这个题可以用一个相当巧妙的前缀和解法来做，复杂度
 * 为 O(n)，而且实现过程没什么坑，很轻松就写完了。这个
 * 方法我是完全没想到的，算是我的知识盲区了。
 */

class Solution {
public:
    int findMaxLength(vector<int>& nums){
        unordered_map<int, int> h;
        int curr = 0, ret = 0;
        h[0] = -1;

        for(int ix = 0; ix != nums.size(); ++ix){
            if(nums[ix]) curr++;
            else curr--;
            if(h.find(curr) == h.end())
                h[curr] = ix;
            if(ret < ix - h[curr])
                ret = ix - h[curr];
        }

        return ret;
    }

    int findMaxLength_dp(vector<int>& nums) {
        int n = nums.size(), cnt;
        vector<int> dp(n, 0);

        for(int ix = 1, jx; ix != n; ++ix){
            int prev = dp[ix-1];
            if(ix-1-prev >= 0 && nums[ix] != nums[ix-1-prev]){
                dp[ix] = dp[ix-1] + 2;
                if(ix-2-prev >= 0)
                    dp[ix] += dp[ix-2-prev];
            }
            else{
                cnt = 0;
                for(jx = ix; jx > ix-1-prev; --jx){
                    if(nums[jx] == 1) ++cnt;
                    else --cnt;
                    if(cnt == 0) break;
                }
                if(cnt == 0){
                    dp[ix] = ix - jx + 1;
                    if(jx-1 >= 0)
                        dp[ix] += dp[jx-1];    
                }
            }
        }

        int ret = 0;
        for(int ix = 0; ix != n; ++ix)
            if(ret < dp[ix]) ret = dp[ix];

        return ret;
    }
};
