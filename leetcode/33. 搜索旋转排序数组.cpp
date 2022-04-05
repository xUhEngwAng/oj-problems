#include <cstdio>
#include <vector>

using std::vector;

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

