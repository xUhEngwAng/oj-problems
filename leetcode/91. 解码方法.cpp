#include <string>
using namespace std;

class Solution {
public:
    int numDecodings(string s) {
        int curr, prev = 1, prevprev = 0;

        for(int ix = 0; ix != s.length(); ++ix){
            curr = 0;
            if(isValid(s.substr(ix, 1))) curr += prev;
            if(1 <= ix && isValid(s.substr(ix-1, 2)))
                curr += prevprev;
            prevprev = prev;
            prev = curr;
        }

        return curr;
    }

    bool isValid(const string& str){
        if(str[0] == '0') return false;
        return stoi(str) <= 26;
    }
};
