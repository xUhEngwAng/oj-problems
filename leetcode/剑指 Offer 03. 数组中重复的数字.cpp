/*
 * 这个题我本来是用了一个hash表来保存出现过的数字，空间复杂度
 * 为 O(1) 的方案我也想到了，无非直接在原始的数组上进行操作。
 * 只是我想象的方案比较复杂，需要循环地把每个值放到它们对应的
 * 位置上，例如 nums[0] = 5，那么记录 5 这个数字已经出现过了，
 * 即 nums[5] = -1，同时需要把 nums[5] 原来的数字继续放到对应
 * 的位置上。这样的解法是比较难写的（所以我也没有写
 *
 * 在评论里面看到一个更好的解法，本质是一样的。但是把 5 放到
 * 对应的位置时，是令 nums[5] -= n，即用绝对值代表这个位置本来
 * 的值，用正负代表这个位置对应的值是否出现过。实现起来简单很多。
 */

class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        int n = nums.size();
        for(auto num : nums){
            if(num < 0) num += n;
            if(nums[num] < 0) return num;
            nums[num] -= n;
        }

        return -1;
    }
};
