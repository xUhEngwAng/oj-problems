#include <string>
#include <vector>
using std::string;
using std::vector;

/*
 * 这个题就是我喜欢的回溯法，但写对的话还是需要有些设计，
 * 我们 brute-force programmer 还是有一点技术含量的。
 *
 * 但其实这个题可以不用回溯，而用 nextpermutation 来做，
 * 具体做法可以参考第 31 题，我也自己想出了解法。这样可以
 * 省掉递归的开销，从而将空间复杂度降低到 O(1)。
 */

class Solution {
public:
    string res;
    vector<string> ret;
    vector<bool> visited;

    void dfs(const string& s, int pos){
        res.push_back(s[pos]);
        visited[pos] = true;
        char prev;

        if(res.length() == s.length()){
            ret.push_back(res);
            goto end;
        }

        for(int ix = 0; ix != s.length(); ++ix){
            if(visited[ix] || s[ix] == prev) continue;
            dfs(s, ix);
            prev = s[ix];
        }

        end:
        res.pop_back();
        visited[pos] = false;
    }

    vector<string> permutation(string s) {
        sort(s.begin(), s.end());
        visited.resize(s.length(), false);
        char prev;

        for(int ix = 0; ix != s.length(); ++ix){
            if(s[ix] == prev) continue;
            dfs(s, ix);
            prev = s[ix];
        }

        return ret;
    }
};
