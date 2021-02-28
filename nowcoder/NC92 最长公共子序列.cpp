class Solution {
public:
    enum dir{LEFT_, UPPER_, DIAG_};
    struct node{
        int maxlen = 0;
        dir direction;
    };
    /**
     * longest common subsequence
     * @param s1 string字符串 the string
     * @param s2 string字符串 the string
     * @return string字符串
     */
    string LCS(string s1, string s2) {
        // write code here
        vector<vector<node>> dp(s1.size()+1, vector<node>(s2.size()+1));
        
        for(int ix = 1; ix <= s1.size(); ++ix){
            for(int jx = 1; jx <= s2.size(); ++jx){
                if(s1[ix-1] == s2[jx-1]){
                    dp[ix][jx].maxlen = dp[ix-1][jx-1].maxlen + 1;
                    dp[ix][jx].direction = DIAG_;
                }
                else
                if(dp[ix][jx-1].maxlen > dp[ix-1][jx].maxlen){
                    dp[ix][jx].maxlen = dp[ix][jx-1].maxlen;
                    dp[ix][jx].direction = LEFT_;
                }    
                else{
                    dp[ix][jx].maxlen = dp[ix-1][jx].maxlen;
                    dp[ix][jx].direction = UPPER_;
                }
            }
        }
        
        if(dp.back().back().maxlen == 0) return "-1";
        
        string ret;
        int row = s1.size(), col = s2.size();
        while(row >= 1 && col >= 1){
            if(s1[row-1] == s2[col-1]) ret.push_back(s1[row-1]);
            switch(dp[row][col].direction){
                case LEFT_:
                    col -= 1;
                    break;
                case UPPER_:
                    row -= 1;
                    break;
                case DIAG_:
                    col -= 1, row -= 1;
                    break;
            }
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};