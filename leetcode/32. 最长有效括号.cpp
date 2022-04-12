#include <string>
using std::string;

class Solution {
public:
    int longestValidParentheses(string s) {
        int left = 0, right = 0, ret = 0;

        for(int ix = 0 ;ix != s.length(); ++ix){
            if(s[ix] == '(') left += 1;
            else right += 1;

            if(left == right && ret < left) ret = left;
            else
            if(left < right) left = right = 0;
        }

        left = right = 0;

        for(int ix = s.length() - 1; ix >= 0; --ix){
            if(s[ix] == ')') right += 1;
            else left += 1;

            if(left == right && ret < right) ret = right;
            else 
            if(right < left) left = right = 0;   
        }

        return ret << 1;
    }
};
