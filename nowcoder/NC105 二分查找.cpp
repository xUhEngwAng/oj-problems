class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 如果目标值存在返回下标，否则返回 -1
     * @param nums int整型vector 
     * @param target int整型 
     * @return int整型
     */
    int search(vector<int>& nums, int target) {
        // write code here
        int left = 0, right = nums.size(), mid;
        
        while(left < right){
            mid = (left + right) >> 1;
            if(target <= nums[mid]) right = mid;
            else                    left = mid + 1;
        }
        
        if(left < nums.size() && nums[left] == target) return left;
        return -1;
    }
};