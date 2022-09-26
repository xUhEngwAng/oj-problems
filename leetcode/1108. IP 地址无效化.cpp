#include <iostream>
#include <string>
using std::string;
using std::cin;
using std::cout;
using std::endl;

class Solution {
public:
    string defangIPaddr(string address) {
        string ret;
        int prevpos = 0, currpos;
        while(true){
            currpos = address.find(".", prevpos);
            cout << "current position is " << currpos << endl;
            if(currpos == string::npos) break;
            ret += address.substr(prevpos, currpos - prevpos);
            ret +=  "[.]";
            prevpos = currpos + 1;
        }
        ret += address.substr(prevpos);
        return ret;
    }
};

int main(){
    string str, res;
    Solution solution;
    while(cin >> str){
        res = solution.defangIPaddr(str);
        cout << res << endl;
    }
    return 0;
}
