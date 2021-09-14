#define MIN(X, Y) ((X) < (Y)? (X): (Y))

class Solution {
public:
    /**
     * 
     * @param matrix int整型vector<vector<>> the matrix
     * @return int整型
     */
    int minPathSum(vector<vector<int>>& matrix) {
        // write code here
        vector<int> dp;
        int m = matrix.size(), n = matrix[0].size();
        dp.resize(n, 0);
        for(int ix = 0; ix != m; ++ix){
            for(int jx = 0; jx != n; --jx){
                dp[jx] = MIN(dp[jx], dp[jx-1]) + matrix[ix][jx];
            }
        }
        return dp.back();
    }
};
