#include <vector>
#define MAX(X, Y) ((X)<(Y)?(Y):(X))
using std::vector;

/*
 * 这个题我居然都没有想出怎么做，可能是脑子糊涂了。既然首尾不能
 * 同时选择，那么答案应该就是 0~n-1 和 1~n 中的最大值。
 */

class Solution {
public:
    int robWithin(const vector<int>& nums, int begin, int end){
        int prev = 0, curr = 0, next;

        for(int ix = begin; ix != end; ++ix){
            next = MAX(curr, prev + nums[ix]);
            prev = curr;
            curr = next;
        }

        return curr;
    }

    int rob(vector<int>& nums) {
        if(nums.size() == 1) return nums[0];
        return MAX(robWithin(nums, 0, nums.size()-1), robWithin(nums, 1, nums.size()));
    }
};
