class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int pos, mask, num1, num2, tmp;
        pos = num1 = num2 = tmp = 0;
        for(auto num : nums)
            tmp = tmp ^ num;
        while(!(tmp & 1)){
            tmp = tmp >> 1;
            pos += 1;
        }
        mask = 1 << pos;
        for(auto num: nums){
            if(num & mask) num1 = num1 ^ num;
            else num2 = num2 ^ num;
        }
        return vector<int>({num1, num2});
    }
};
