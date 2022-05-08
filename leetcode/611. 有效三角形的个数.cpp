#include <algorithm>
#include <vector>
using namespace std;

/*
 * 又没有写出最优解，非常惭愧。我的解法是个 O(n^2logn) 的
 * 接近暴力解，实际上这个题和「三数之和」没有任何区别，使
 * 双指针即可将复杂度降低到 O(n^2)，编码上也更加容易。
 */

class Solution {
public:
    int triangleNumber(vector<int>& nums){
        int ret = 0, n = nums.size(), curr, begin, end;
        sort(nums.begin(), nums.end());

        for(int ix = n - 1; ix >= 2; --ix){
            curr = nums[ix];
            begin = 0, end = ix - 1;
            while(begin < end){
                if(nums[begin] + nums[end] <= curr){
                    ++begin;
                    continue;
                }
                ret += end - begin;
                end--;
            }
        }

        return ret;
    }

    int triangleNumber_binary_search(vector<int>& nums) {
        int ret = 0, n = nums.size(), sum, pos;
        sort(nums.begin(), nums.end());
        
        for(int begin = 0; begin < n-2; ++begin){
            for(int end = begin + 1; end < n-1; ++end){
                sum = nums[begin] + nums[end];
                pos = binarySearch(nums, end+1, n, sum);
                ret += pos - end;
            }
        }

        return ret;
    }

    int binarySearch(const vector<int>& nums, int begin, int end, int target){
        int mid;
        while(begin < end){
            mid = (begin + end) >> 1;
            if(target <= nums[mid]) end = mid;
            else begin = mid + 1;
        }

        return begin-1;
    }
};
