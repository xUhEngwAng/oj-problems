#include <vector>
#include <string>

using std::vector;
using std::string;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        std::vector<bool> exist(128, false);
        int start = 0, currLen = 0, maxLen = 0;

        for(int ix = 0; ix != s.length(); ++ix){
            char ch = s[ix];
            if(exist[ch]){
                do{
                    exist[s[start]] = false;
                    currLen -= 1;
                } while(s[start++] != ch);
            }
            exist[ch] = true;
            if(++currLen > maxLen) maxLen = currLen;
        }

        return maxLen;
    }
};
