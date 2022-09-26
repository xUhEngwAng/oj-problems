class Solution {
public:
    string generateTheString(int n) {
        string ret(n-1, 'a');
        if(n & 1) ret.push_back('a');
        else ret.push_back('b');
        return ret;
    }
};
