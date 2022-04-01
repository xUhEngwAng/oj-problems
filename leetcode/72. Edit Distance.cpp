#include <iostream>
#include <string>
#include <vector>
#define MIN(X, Y) ((X)<(Y)?(X):(Y))
#define MIN3(X, Y, Z) MIN(MIN(X, Y), Z)

using std::string;
using std::vector;

/*
 * 在dp数组初始化那里卡了好久，一开始是把边缘部分初始化为0，
 * 后来改为初始化为1，后来才发现应该初始化为更长的string的长度。
 */ 

class Solution {
public:
    int minDistance(string word1, string word2){
        int m = word1.length(), n = word2.length();
        std::vector<std::vector<int>> dp(m+1, std::vector<int>(n+1, 1));
        for(int ix = 0; ix <= m; ++ix)
            dp[ix][0] = ix;
        for(int jx = 0; jx <= n; ++jx)
            dp[0][jx] = jx;

        for(int ix = 0; ix != m; ++ix){
            for(int jx = 0; jx != n; ++jx){
                if(word1[ix] == word2[jx])
                    dp[ix+1][jx+1] = dp[ix][jx];
                else
                    dp[ix+1][jx+1] = MIN3(dp[ix+1][jx], dp[ix][jx+1], dp[ix][jx]) + 1;
            }
        }

        return dp[m][n];
    }
};

int main(){
    std::string word1 = "plasma";
    std::string word2 = "altruism";
    Solution solution;
    int res = solution.minDistance(word1, word2);
    std::cout << "The answer is " << res << std::endl;
    return 0;
}

