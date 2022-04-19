#include <iostream>
#include <algorithm>
#include <vector>
using std::sort;
using std::vector;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ret, curr;
        int prev = 0x7fffffff;

        for(int ix = nums.size() - 1; ix >= 0; --ix){
            if(nums[ix] == prev) continue;
            curr = twoSum(nums, -nums[ix], 0, ix-1);
            for(auto v : curr){
                v.push_back(nums[ix]);
                ret.push_back(v);
            }
            prev = nums[ix];
        }

        return ret;
    }

    vector<vector<int>> twoSum(const vector<int>& nums, int target, int begin, int end) {
        vector<vector<int>> ret;
        int sum;

        while(begin < end){
            sum = nums[begin] + nums[end];
            if(sum < target) 
                while(++begin < end && nums[begin] == nums[begin-1]);
            else if(target < sum)
                while(--end > begin && nums[end] == nums[end+1]);
            else{
                ret.push_back({nums[begin], nums[end]});    
                while(++begin < end && nums[begin] == nums[begin-1]); 
                while(--end > begin && nums[end] == nums[end+1]);
            }
        }

        return ret;
    }
};

int main(){
    int n;
    std::cin >> n;
    vector<int> nums(n);
    for(int ix = 0; ix != n; ++ix)
        std::cin >> nums[ix];

    Solution solution;
    vector<vector<int>> res = solution.threeSum(nums);
    for(auto v : res){
        std::cout << "[" << v[0] << ", " << v[1] << ", " << v[2] << "]" << std::endl;
    }

    return 0;
}
