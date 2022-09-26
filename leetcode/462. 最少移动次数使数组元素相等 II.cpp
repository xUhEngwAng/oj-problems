#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int minMoves2(vector<int>& nums) {
        long long ret = 0, target = median(nums);
        for(auto e : nums)
            ret += abs(e - target);
        return ret;
    }

    int median(vector<int>& nums){
        int n = nums.size(), begin = 0, end = n, curr, k = n >> 1;
        while(true){
            curr = partition(nums, begin, end);
            if(curr < k) begin = curr + 1;
            else if (k < curr) end = curr;
            else break;
        }
        return nums[curr];
    }

    void swap(vector<int> &nums, int lh, int rh){
        int tmp = nums[lh];
        nums[lh] = nums[rh];
        nums[rh] = tmp;
    }

    int partition(vector<int>& nums, int begin, int end){
        int mid = (begin + end) >> 1;
        vector<int> v = {begin, mid, end};
        sort(v.begin(), v.end(), [nums](int lh, int rh){return nums[lh] < nums[rh];});
        swap(nums, begin, v[1]);
        int pivot = nums[begin];
        while(true){
            while(begin < --end && pivot <= nums[end]);
            if(begin == end) break;
            nums[begin] = nums[end];

            while(++begin < end && nums[begin] <= pivot);
            if(begin == end) break;
            nums[end] = nums[begin];
        }
        nums[begin] = pivot;
        return begin;
    }
};

int main(){
    int n;
    cin >> n;
    vector<int> nums(n);
    for(int ix = 0; ix != n; ++ix)
        cin >> nums[ix];

    Solution solution;
    int ans = solution.minMoves2(nums);
    cout << "The answer is " << ans << endl;
    return 0;
}
