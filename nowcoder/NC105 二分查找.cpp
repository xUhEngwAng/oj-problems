class Solution {
public:
    /**
     * 二分查找
     * @param n int整型 数组长度
     * @param v int整型 查找值
     * @param a int整型vector 有序数组
     * @return int整型
     */
    int upper_bound_(int n, int v, vector<int>& a) {
        // write code here
        int left = 0, right = n, mid;
        
        while(left < right){
            mid = (left + right) >> 1;
            if(v <= a[mid]) right = mid;
            else            left  = mid + 1;
        }
        
        return right + 1;
    }
};