class Solution {
public:
    vector<bool> prefixesDivBy5(vector<int>& nums) {
        vector<bool> ret;
        int curr = 0;
        for(auto num : nums){
            curr = (curr << 1) + num;
            if((curr = curr % 5) == 0) ret.push_back(true);
            else ret.push_back(false);
        }
        return ret;
    }
};
