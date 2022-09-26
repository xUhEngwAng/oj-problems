class Solution {
public:
    vector<int> minSubsequence(vector<int>& nums) {
        int total = 0, sum = 0;
        vector<int> ret;
        
        for(auto num : nums){
            total += num;
        }

        make_heap(nums.begin(), nums.end());
        
        while(sum <= total - sum){
            pop_heap(nums.begin(), nums.end());
            ret.push_back(nums.back());
            sum += nums.back();
            nums.pop_back();
        }

        return ret;
    }
};
