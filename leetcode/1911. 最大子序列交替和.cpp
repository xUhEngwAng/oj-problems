#include <vector>
#define MIN(X, Y) ((X)<(Y)?(X):(Y))
#define MAX(X, Y) ((X)<(Y)?(Y):(X))
using std::vector;

/*
 * 这个题解虽然短，但是我不会做...
 * 思路方面我首先是想了分治，可以遍历每个位置，从该位置将 nums 分成
 * 两个部分，每个部分分别计算交替和，最终的答案为 front+end-nums[ix]
 * 但是这个方法的复杂度为 O(n^2)。
 *
 * 然后考虑dp。我想到了使用 dp[ix] 表示前 ix 个元素的最大交替和，然
 * 而如何进行状态转移就成了一个问题，如果不使用 nums[ix] 自然好说，
 * 直接就是 dp[ix]=dp[ix-1]。但如果使用 nums[ix]，则要在 nums[ix] 前
 * 再使用一个元素，考虑起来非常复杂。
 *
 * 实际上我只差了一步。如果使用 even[ix] 表示前 ix 个元素中包含偶数
 * 个元素的子序列的最大交替和，odd[ix] 同理。则可以很容易更新 odd[ix]
 *
 * odd[ix] = MAX(odd[ix-1], even[ix-1] + nums[ix])
 *
 * 同理，更新 even[ix] 也只需要 O(1) 的时间。
 */

class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int odd = nums[0], even = 0, tmp;
        int n = nums.size();

        for(int ix = 1; ix != n; ++ix){
            tmp  = MAX(odd, even+nums[ix]);
            even = MAX(even, odd-nums[ix]);
            odd  = tmp;
        }

        return odd;
    }
};
