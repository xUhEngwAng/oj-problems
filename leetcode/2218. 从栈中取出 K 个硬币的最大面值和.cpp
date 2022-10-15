#include <vector>
#define MAX(X, Y) ((X)<(Y)?(Y):(X))
using std::vector;

/*
 * 之前没写过分组背包，状态转移方程跟 01 背包是类似的，只不过每一步
 * 都枚举组内的所有 item，然后选择最大值。写起来跟 01 背包差不多，
 * 同样可以使用滚动数组进行优化。
 */

class Solution {
public:
    int maxValueOfCoins(vector<vector<int>>& piles, int k) {
        int n = piles.size();
        vector<vector<int>> prefixSum(n);

        for(int ix = 0; ix != n; ++ix){
            prefixSum[ix].push_back(piles[ix][0]);
            
            for(int jx = 1; jx != piles[ix].size(); ++jx){
                prefixSum[ix].push_back(prefixSum[ix].back() + piles[ix][jx]);
            }
        }

        vector<int> dp(k+1);

        for(int ix = 0; ix != n; ++ix){
            for(int jx = k; jx > 0; --jx){
                for(int kx = 0; kx != prefixSum[ix].size(); ++kx){
                    if(jx <= kx) continue;
                    dp[jx] = MAX(dp[jx], dp[jx-kx-1]+prefixSum[ix][kx]);
                }
            }
        }

        return dp[k];
    }
};
