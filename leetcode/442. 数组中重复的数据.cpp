#include <vector>
using std::vector;

/*
 * 简单说来本题的思路就是做一个原地hash，即将原始的vector
 * 同时也作为hash表。但是这个代码逻辑是真的够复杂的，有很多
 * 边界情况需要处理。
 */

class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        int curr, next;
        vector<int> ret;

        for(int ix = 0; ix != nums.size(); ++ix){
            if(nums[ix] <= 0) continue;
            if(nums[ix] == ix + 1){
                nums[ix] = -1;
                continue;
            }
            curr = nums[ix];
            nums[ix] = 0;

            while(true){
                if(nums[curr-1] < 0){
                    ret.push_back(curr);
                    break;
                }
                else{
                    next = nums[curr-1];
                    nums[curr-1] = -1;
                    curr = next;
                }
                if(curr == 0) break;
            }
        }

        return ret;
    }
};
