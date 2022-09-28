class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int curr = nums[0], cnt = 1, n = nums.size();

        for(int ix = 1; ix != n; ++ix){
            if(nums[ix] == curr) cnt += 1;
            else cnt -= 1;
            if(cnt == 0 && ix < n - 1) curr = nums[ix + 1];
        } 

        return curr;
    }
};
