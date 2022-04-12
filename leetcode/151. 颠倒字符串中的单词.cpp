#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

class Solution {
public:
    string reverseWords(string s) {
        vector<string> splitted_words = split(s);
        std::reverse(splitted_words.begin(), splitted_words.end());
        string ret = "";
        for(auto word : splitted_words){
            ret = ret + word + " ";
        }

        return ret.substr(0, ret.length()-1);
    }

    vector<string> split(string s){
        vector<string> ret;
        int start, end = -1;

        while(true){
            start = s.find_first_not_of(" ", end + 1);
            if(start == s.npos) break;
            end = s.find(" ", start);
            if(end == s.npos) break;
            ret.push_back(s.substr(start, end-start));
        }

        if(start != s.npos) ret.push_back(s.substr(start));
        return ret;
    }
};

int main(){
    string s;
    getline(std::cin, s);
    Solution solution;
    string reversed_str = solution.reverseWords(s);
    std::cout << reversed_str << std::endl;
    return 0;
}
