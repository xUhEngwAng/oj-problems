#define MIN(X, Y) ((X) < (Y)? (X): (Y))
#define MAX(X, Y) ((X) > (Y)? (X): (Y))
class Solution {
public:
    /**
     * max water
     * @param arr int整型vector the array
     * @return long长整型
     */
    long long maxWater(vector<int>& arr) {
        // write code here
        vector<int> left_height, right_height;
        left_height.resize(arr.size());
        right_height.resize(arr.size());
        left_height[0] = 0;
        for(int ix = 1; ix != arr.size(); ++ix){
            left_height[ix] = MAX(left_height[ix-1], arr[ix-1]); 
        }
        right_height.back() = 0;
        for(int ix = arr.size() - 2; ix >= 0; --ix){
            right_height[ix] = MAX(right_height[ix+1], arr[ix+1]);
        }
        long long ret = 0;
        for(int ix = 0; ix != arr.size(); ++ix){
            ret += MAX(MIN(left_height[ix], right_height[ix]) - arr[ix], 0);
        }
        return ret;
    }
};
