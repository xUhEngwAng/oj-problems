#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int m = s1.length(), n = s2.length(), shift = 0;
        if(n < m) return false;

        vector<int> chcnt(26);
        for(int ix = 0; ix != m; ++ix){
            chcnt[s1[ix]-'a'] += 1;
            chcnt[s2[ix]-'a'] -= 1;
        }
        for(int jx = 0; jx != chcnt.size(); ++jx){
            shift += abs(chcnt[jx]);
        }
        if(shift == 0) return true;

        for(int ix = m; ix != n; ++ix){
            if(chcnt[s2[ix-m]-'a']++ < 0) shift--;
            else shift++;
            if(chcnt[s2[ix]-'a']-- > 0) shift--;
            else shift++;
            if(shift == 0) return true;
        }

        return false;
    }
};
