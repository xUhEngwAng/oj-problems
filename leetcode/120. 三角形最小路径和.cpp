#include <vector>
#define INF (0x7fffffff)
#define MIN(X, Y) ((X)<(Y)?(X):(Y))
using namespace std;

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        vector<int> dp;
        dp.resize(triangle.back().size(), INF);
        dp[0] = triangle[0][0];

        for(int ix = 1; ix != triangle.size(); ++ix){
            for(int jx = triangle[ix].size()-1; jx >= 0; --jx){
                int left = jx>0?dp[jx-1]: INF;
                int right = dp[jx];
                dp[jx] = MIN(left, right) + triangle[ix][jx];
            }
        }

        int ret = INF;
        for(int ix = 0; ix != dp.size(); ++ix)
            if(dp[ix] < ret) ret = dp[ix];
        return ret;
    }
};
