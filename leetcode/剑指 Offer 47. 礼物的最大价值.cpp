#include <vector>
#define MAX(X, Y) ((X)<(Y)?(Y):(X))
using std::vector;

class Solution {
public:
    int maxValue(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<int> dp(n+1, 0);

        for(int ix = 0; ix != m; ++ix){
            for(int jx = 1; jx <= n; ++jx){
                dp[jx] = MAX(dp[jx], dp[jx-1]) + grid[ix][jx-1];
            }
        }

        return dp[n];
    }
};
