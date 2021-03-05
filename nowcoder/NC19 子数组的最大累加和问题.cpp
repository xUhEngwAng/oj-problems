class Solution {
public:
    /**
     * max sum of the subarray
     * @param arr int整型vector the array
     * @return int整型
     */
    int maxsumofSubarray(vector<int>& arr) {
        // write code here
        int curr = 0, max = 0;
        
        for(int ix = 0; ix != arr.size(); ++ix){
            curr += arr[ix];
            if(max < curr) max = curr;
            if(curr < 0) curr = 0;
        }
        
        return max;
    }
};