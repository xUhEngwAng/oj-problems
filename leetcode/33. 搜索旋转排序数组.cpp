#include <cstdio>
#include <vector>
using std::vector;

/*
 * 这个题我此前的思路是使用三次二分查找，第一次二分先找到划分的位置。
 * 实际上，只使用一次二分查找就可以完成目标值的搜索。
 *
 * 这里的做法是，比较 target 和 nums[mid]，然而 target 和 nums[mid]
 * 确可能处于 nums 不同段（前半段或者后半段），直接比较两者是没有
 * 意义的。因此，如果两者处于不同段，则调整 begin 或者 end 使得 mid
 * 靠近 target 所在的段。如果两者处于一段，则使用常规的二分查找。这
 * 个算法的正确性可以使用循环不变式证明。
 */

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int begin = 0, end = nums.size(), mid;
        bool isFront = (nums[0] <= target);

        while(begin < end){
            mid = (begin + end) >> 1;
            if( isFront && nums[mid] < nums[0]) { end = mid; continue; }
            if(!isFront && nums[0] < nums[mid]) { begin = mid + 1; continue; }

            if(target < nums[mid]) end = mid;
            else if(nums[mid] < target) begin = mid + 1;
            else return mid;
        }

        return -1;
    }
};

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int begin = 0, end = nums.size(), mid, pos;

        while(begin < end){
            mid = (begin + end) >> 1;
            if(nums[mid] < nums[0]) end = mid;
            else begin = mid + 1;
        }


        pos = binarySearch(nums, 0, begin, target);
        if(pos == -1) pos = binarySearch(nums, begin, nums.size(), target);
        return pos;
    }

    int binarySearch(vector<int>& nums, int begin, int end, int target){
        int mid;

        while(begin < end){
            mid = (begin + end) >> 1;
            if(target < nums[mid]) end = mid;
            else if(nums[mid] < target) begin = mid + 1;
            else return mid;
        }

        return -1;
    }
};

int main(){
    int n, target;
    scanf("%d", &n);
    vector<int> nums(n);
    for(int ix = 0; ix != n; ++ix){
        scanf("%d", &nums[ix]);
    }
    scanf("%d", &target);

    Solution solution;
    int pos = solution.search(nums, target);
    printf("The result is %d.\n", pos);
    return 0;
}

