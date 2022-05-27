#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

/*
 * 此题我一开始写的双指针法，就是 TwoSum 的变体，时间和空间复杂度
 * 分别是 O(nlogn) 和 O(logn)。看到题解恍然大雾可以用 hash 表来做，
 * 时间和空间复杂度分别是 O(n) 和 O(n)。然而实际情况是第一种方法的
 * 运行时间更少，可能是因为 hash 常数太大或者太多冲突了吧。
 *
 * 写 hash 解法的时候也需要注意，不能简单用 unordered_set 来保存
 * 出现过的数字，因为可能同一个数字一开始出现多次，每次出现都可以
 * 和后面的某个数字匹配上。因此要用 unordered_map 保存出现的次数。
 */

class Solution {
public:
    int maxOperations(vector<int>& nums, int k){
        unordered_map<int, int> appear_cnt;
        int ret = 0, target;

        for(auto e : nums){
            target = k - e;
            if(appear_cnt.find(target) != appear_cnt.end() && appear_cnt[target]){
                appear_cnt[target] -= 1;
                ret += 1;
            }
            else appear_cnt[e] += 1;
        }

        return ret;
    }

    int maxOperations_origin(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int begin = 0, end = nums.size() - 1, ret = 0;

        while(begin < end){
            if(nums[begin] + nums[end] < k) ++begin;
            else if(k < nums[begin] + nums[end]) --end;
            else {++ret; ++begin; --end;}
        }

        return ret;
    }
};
