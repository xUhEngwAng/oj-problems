#define MIN(X, Y) ((X) < (Y)? (X): (Y))

class Solution {
public:
    /**
     * min edit cost
     * @param str1 string字符串 the string
     * @param str2 string字符串 the string
     * @param ic int整型 insert cost
     * @param dc int整型 delete cost
     * @param rc int整型 replace cost
     * @return int整型
     */
    int min(int x, int y, int z){
        return MIN(MIN(x, y), z);
    }
    
    int minEditCost(string str1, string str2, int ic, int dc, int rc) {
        // write code here
        int m = str1.length(), n = str2.length();
        vector<vector<int>> dp;
        dp.resize(m+1, vector<int>(n+1, 0));
        
        for(int ix = 0; ix != n; ++ix)
            dp[0][ix] = ix * ic;
        for(int ix = 0; ix != m; ++ix)
            dp[ix][0] = ix * dc;
        
        for(int ix = 1; ix <= m; ++ix){
            for(int jx = 1; jx <= n; ++jx){
                if(str1.at(ix-1) == str2.at(jx-1))
                    dp[ix][jx] = dp[ix-1][jx-1];
                else{
                    dp[ix][jx] = min(dp[ix-1][jx-1]+rc, 
                                     dp[ix-1][jx]+dc, 
                                     dp[ix][jx-1]+ic);
                }
            }
        }
        return dp[m][n];
    }
};
