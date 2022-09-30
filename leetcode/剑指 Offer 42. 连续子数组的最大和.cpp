class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int curr = 0, ret = 0x89000000;

        for(auto num : nums){
            curr += num;
            if(ret < curr) ret = curr;
            if(curr < 0) curr = 0;
        }

        return ret;
    }
};
