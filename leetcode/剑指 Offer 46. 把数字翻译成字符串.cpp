#include <string>
using namespace std;

class Solution {
public:
    int translateNum(int num) {
        string str = to_string(num);
        int prevprev = 1, prev = 1, curr = 1;

        for(int ix = 1; ix != str.length(); ++ix){
            curr = prev;
            if(str[ix-1] != '0' && stoi(str.substr(ix-1, 2)) <= 25)
                curr += prevprev;
            prevprev = prev;
            prev = curr;
        }

        return curr;
    }
};
