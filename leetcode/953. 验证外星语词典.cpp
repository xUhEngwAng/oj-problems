#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<int> alphabet;

    bool isAlienSorted(vector<string>& words, string order) {
        alphabet.resize(26);
        for(int ix = 0; ix != order.length(); ++ix)
            alphabet[order[ix]-'a'] = ix;

        for(int ix = 1; ix != words.size(); ++ix){
            if(!inOrder(words[ix-1], words[ix]))
                return false;
        }

        return true;
    }

    bool inOrder(const string& lhs, const string& rhs){
        int m = lhs.length(), n = rhs.length(), len = m<n?m:n, pos;
        for(pos = 0; pos != len; ++pos)
            if(lhs[pos] != rhs[pos])
                break;

        if(pos == len) return m <= n;
        return alphabet[lhs[pos]-'a'] < alphabet[rhs[pos]-'a'];
    }
};
