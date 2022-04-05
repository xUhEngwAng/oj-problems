#include <iostream>
#include <vector>
using std::vector;

class Solution{
public:
    int lengthOfLIS(vector<int>& nums){
        vector<int> seq;
        int pos;

        for(auto num : nums){
            pos = binarySearch(seq, num);
            if(seq.size() == pos) seq.push_back(num);
            else seq[pos] = num;
        }

        return seq.size();
    }

    int binarySearch(vector<int>& nums, int val){
        int begin = 0, end = nums.size(), mid;

        while(begin < end){
            mid = (begin + end) >> 1;
            if(val < nums[mid]) end = mid;
            else if(nums[mid] < val) begin = mid + 1;
            else return mid;
        }

        return begin;
    }
};

int main(){
    int n;
    scanf("%d", &n);
    vector<int> nums(n);
    for(int ix = 0; ix != n; ++ix)
        scanf("%d", &nums[ix]);

    Solution solution;
    int res = solution.lengthOfLIS(nums);
    printf("The LIS of nums is %d.\n", res);
    return 0;
}

