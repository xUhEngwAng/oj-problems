class Solution {
public:
    /**
     * longest common substring
     * @param str1 string字符串 the string
     * @param str2 string字符串 the string
     * @return string字符串
     */
    string LCS(string str1, string str2) {
        // write code here
        int maxrow = 0, maxcol = 0, maxlen;
        vector<vector<int>> dp(str1.size() + 1, vector<int>(str2.size() + 1, 0));
        
        for(int ix = 1; ix <= str1.size(); ++ix){
            for(int jx = 1; jx <= str2.size(); ++jx){
                if(str1[ix-1] != str2[jx-1]) continue;
                dp[ix][jx] = dp[ix-1][jx-1] + 1;
                if(dp[maxrow][maxcol] < dp[ix][jx]){
                    maxrow = ix;
                    maxcol = jx;
                }
            }
        }
        
        string ret;
        maxlen = dp[maxrow][maxcol];
        
        while(maxlen--){
            ret.push_back(str1[--maxrow]);
        }
        
        reverse(ret.begin(), ret.end());
        return ret;
    }
};