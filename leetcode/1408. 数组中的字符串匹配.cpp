/*
 * 这个题我本来不想写暴力解，想着小小优化一下，结果力速双A （指用时
 * 和内存都超过了 5% 的用户。想了下可能是这个优化解法内存存取量还挺
 * 大的，而且也用到了一个 hash 表，常数比较大，也合理吧。
 */

class Solution {
public:
    vector<string> stringMatching(vector<string>& words) {
        vector<string> ret;

        for(int ix = 0; ix != words.size(); ++ix){
            for(int jx = 0; jx != words.size(); ++jx){
                if(jx == ix) continue;
                if(words[jx].find(words[ix]) != string::npos){
                    ret.push_back(words[ix]);
                    break;
                }
            }
        }

        return ret;
    }

    unordered_set<string> substrs;

    vector<string> stringMatching(vector<string>& words) {
        for(auto word : words){
            appendWord(word);
        }

        vector<string> ret;

        for(auto word : words){
            if(substrs.find(word) != substrs.end())
                ret.push_back(word);
        }

        return ret;
    }

    void appendWord(const string &word){
        int m = word.length();

        for(int ix = 1; ix != m; ++ix){
            for(int jx = 0; ix+jx <= m; ++jx){
                substrs.insert(word.substr(jx, ix));
            }
        }
    }
};
