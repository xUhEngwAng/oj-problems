class Solution {
public:
    void swap(int &lh, int &rh){
        int tmp = lh;
        lh = rh;
        rh = tmp;
    }

    vector<int> exchange(vector<int>& nums) {
        int begin = -1, end = nums.size();

        while(true){
            while(++begin < end && (nums[begin] & 1));
            while(--end > begin && !(nums[end] & 1));
            if(end <= begin) break;
            swap(nums[begin], nums[end]);
        }

        return nums;
    }
};
