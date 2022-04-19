#include <cstdio>
#include <string>
#include <vector>
using std::string;
using std::vector;

class Solution {
public:
    string curr;
    vector<string> ret;

    vector<string> generateParenthesis(int n) {
        dfs('(', n, 1, 0);
        return ret;
    }

    void dfs(char ch, int n, int left_cnt, int right_cnt){
        curr.push_back(ch);
        if(left_cnt == n && right_cnt == n){
            ret.push_back(curr);
            goto clean;
        }

        if(right_cnt < left_cnt) 
            dfs(')', n, left_cnt, right_cnt + 1);
        if(left_cnt < n) 
            dfs('(', n, left_cnt + 1, right_cnt);

        clean:
        curr.pop_back();
    }
};
