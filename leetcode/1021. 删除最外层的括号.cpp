#include <string>
using namespace std;

class Solution {
public:
    string removeOuterParentheses(string s) {
        int left_cnt, right_cnt, start = 0, end = 0;
        string ret;

        while(start < s.length()){
            left_cnt = right_cnt = 0;
            while(true){
                if(s[end] == '(') left_cnt++;
                else right_cnt++;
                if(left_cnt == right_cnt) break;
                ++end;
            }
            ret += s.substr(start+1, end-start-1);
            start = ++end;
        }

        return ret;
    }
};
