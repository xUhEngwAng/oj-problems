class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param nums intvector 
     * @return intvector<vector<>>
     */
    vector<vector<int>> foundMonotoneStack(vector<int>& nums) {
        // write code here
        vector<int> left, right;
        int n = nums.size(), curr;
        left.resize(n, -1);
        right.resize(n, -1);
        
        for(int ix = 1; ix != n; ++ix){
            curr = ix - 1;
            while(curr != -1){
                if(nums[curr] < nums[ix]){
                    left[ix] = curr;
                    break;
                }
                if(nums[curr] == nums[ix]){
                    left[ix] = left[curr];
                    break;
                }
                curr = left[curr];
            }
        }
        
        for(int ix = n - 2; ix >= 0; --ix){
            curr = ix + 1;
            while(curr != -1){
                if(nums[curr] < nums[ix]){
                    right[ix] = curr;
                    break;
                }
                if(nums[curr] == nums[ix]){
                    right[ix] = right[curr];
                    break;
                }
                curr = right[curr];
            }
        }
        
        vector<vector<int>> ret;
        for(int ix = 0; ix != n; ++ix){
            ret.push_back({left[ix], right[ix]});
        }
        return ret;
    }
};
