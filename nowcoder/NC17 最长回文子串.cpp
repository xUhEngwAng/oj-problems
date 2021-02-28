class Solution {
public:
    int PalindromeLength(const string& str, int center, int bias){
        int ret = 0, len = str.length();
        
        while(true){
            if(center + bias + ret >= len) break;
            if(center - bias - ret < 0)    break;
            if(str[center + bias + ret] != str[center - bias - ret]) break;
            ++ret;
        }
        
        return ret;
    }
    
    int getLongestPalindrome(string A, int n) {
        // write code here
        if(n == 0) return 0;
        
        int len = (n << 1) + 1, front, jx, pos;
        string str;
        vector<int> dp(len, 1);
        str.reserve(len);
        
        for(int ix = 0; ix != len; ++ix){
            if(ix & 1) str.push_back(A[ix >> 1]);
            else       str.push_back('-');
        }
        
        pos = front = 0;
        
        for(int ix = 1; ix != len; ++ix){
            if(front < ix){
                dp[ix] = PalindromeLength(str, ix, 0);
                front = ix + dp.back() - 1;
                pos = ix;
                continue;
            }
            
            jx = (pos << 1) - ix;
            if(dp[jx] < front - ix + 1) dp[ix] = dp[jx];
            else 
            if(dp[jx] > front - ix + 1) dp[ix] = front - ix + 1;
            else
                dp[ix] = front - ix + 1 + PalindromeLength(str, ix, front - ix + 1);
            
            if(ix + dp[ix] - 1 > front){
                front = ix + dp[ix] - 1;
                pos = ix;
            }
        }
        
        int ret = 1;
        
        for(int ix = 0; ix != len; ++ix){
            if(ret < dp[ix]) ret = dp[ix];
        }
        
        return ret - 1;
    }
};