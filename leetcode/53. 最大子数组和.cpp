class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int ret = 0x80000000, curr = 0;

        for(auto num : nums){
            curr = curr + num;
            if(ret < curr) ret = curr;
            if(curr < 0) curr = 0;
        }

        return ret;
    }
};
