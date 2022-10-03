#include <vector>
#include <string>
#define MAX(X, Y) ((X)<(Y)?(Y):(X))

using namespace std;

class Solution {
public:
    void countZeroOne(const string& str, int& zero_cnt, int& one_cnt){
        zero_cnt = one_cnt = 0;

        for(auto ch : str){
            if(ch == '0') zero_cnt += 1;
            else one_cnt += 1;
        }
    }

    int findMaxForm(vector<string>& strs, int m, int n) {
        int zero_cnt, one_cnt;
        vector<vector<int>> dp(m+1, vector<int>(n+1));

        for(int ix = 0; ix != strs.size(); ++ix){
            countZeroOne(strs[ix], zero_cnt, one_cnt);
            
            for(int jx = m; jx >= 0; --jx){
                for(int kx = n; kx >= 0; --kx){
                    if(jx < zero_cnt || kx < one_cnt) continue;
                    dp[jx][kx] = MAX(dp[jx][kx], dp[jx-zero_cnt][kx-one_cnt] + 1);
                }
            }
        }

        return dp[m][n];
    }
};
