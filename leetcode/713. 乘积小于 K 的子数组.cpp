#include <iostream>
#include <vector>
using namespace std;

/*
 * 这个题看起来很简单，实际写的时候需要注意的细节还是不少的。
 */

class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int start, end, curr = 1, ret = 0;
        int n = nums.size();

        for(start = 0, end = 0; start != n; ++start){
            while(end < n){
                if(k <= curr*nums[end]) break;
                curr = curr * nums[end];
                ++end;
            }
            ret += end - start;
            if(end == start) ++end;
            else curr = curr / nums[start];
        }

        return ret;
    }
};

int main(){
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    for(int ix = 0; ix != n; ++ix)
        cin >> nums[ix];

    Solution solution;
    int ans = solution.numSubarrayProductLessThanK(nums, k);
    cout << "The answer is " << ans << endl;
    return 0;
}
