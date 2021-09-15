class Solution {
public:
    const int INF = 0x80000000;
    int findPeakElement(vector<int>& nums) {
        int begin = 0, end = nums.size(), mid;
        int prev, next;
        while(begin < end){
            mid = (begin + end) >> 1;
            prev = (mid-1<begin? INF: nums[mid-1]);
            next = (mid+1==end? INF: nums[mid+1]);
            if(nums[mid] < next) begin = mid + 1;
            else if(nums[mid] < prev) end = mid;
            else return mid;
        }
        return -1;
    }
};
