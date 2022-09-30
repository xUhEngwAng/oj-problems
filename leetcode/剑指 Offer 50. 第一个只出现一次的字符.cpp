#include <vector>
#include <string>
using std::vector;
using std::string;

class Solution {
public:
    char firstUniqChar(string s) {
        vector<pair<int, int>> ch_cnt(26, pair<int, int>(-1, 0));

        for(int ix = 0; ix != s.length(); ++ix){
            int ch = s[ix] - 'a';
            if(!ch_cnt[ch].second) ch_cnt[ch].first = ix;
            ch_cnt[ch].second += 1;
        }

        int min_pos = s.length();

        for(int ix = 0; ix != ch_cnt.size(); ++ix){
            if(ch_cnt[ix].second != 1) continue;
            if(ch_cnt[ix].first < min_pos) min_pos = ch_cnt[ix].first;
        }

        return min_pos == s.length()? ' ' : s[min_pos];
    }
};
