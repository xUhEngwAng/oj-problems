#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int m = p.length(), n = s.length(), shift = 0;
        if(n < m) return vector<int>();

        vector<int> chcnt(26), ret;
        for(int ix = 0; ix != m; ++ix){
            chcnt[p[ix]-'a'] += 1;
            chcnt[s[ix]-'a'] -= 1;
        }
        for(int jx = 0; jx != chcnt.size(); ++jx){
            shift += abs(chcnt[jx]);
        }
        if(shift == 0) ret.push_back(0);

        for(int ix = m; ix != n; ++ix){
            if(chcnt[s[ix-m]-'a']++ < 0) shift--;
            else shift++;
            if(chcnt[s[ix]-'a']-- > 0) shift--;
            else shift++;
            if(shift == 0) ret.push_back(ix-m+1);
        }

        return ret;
    }
};
