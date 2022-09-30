#include <vector>
using std::vector;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int begin = 0, end = nums.size() - 1, sum;

        while(begin < end){
            sum = nums[begin] + nums[end];
            if(sum < target) begin += 1;
            else if(target < sum) end -= 1;
            else return vector<int>({nums[begin], nums[end]});
        }

        return vector<int>();
    }
};
