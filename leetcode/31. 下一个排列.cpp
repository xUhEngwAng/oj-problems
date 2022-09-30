#include <algorithm>
#include <vector>
using std::reverse;
using std::vector;

/* 
 * 这个题还挺有意思的，想了好一会儿自己想出来了。我的做法相对
 * 于官方的不足主要在于最后一步，我是用了个 sort，而实际上后面
 * 的序列一定的逆序的，所以用一个 reverse 就可以了，这样可以把
 * 最坏情况的时间复杂度降到 O(n)，其中 n 为序列的长度。
 */

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int src, target = 0, tmp;

        for(src = nums.size() - 2; src >= 0; --src){
            if(nums[src] < nums[src + 1]) break;
        }

        if(src >= 0){
            for(target = nums.size() - 1; target >= src; --target){
                if(nums[src] < nums[target]) break;
            }

            tmp = nums[src];
            nums[src] = nums[target];
            nums[target] = tmp;
        }

        reverse(nums.begin() + src + 1, nums.end());
    }
};
