#include <string>
#include <vector>
#include <unordered_map>
#define MAX (0x7fffffff)
using namespace std;


class Solution {
public:
    unordered_map<string, vector<int>> wordpos;

    int findClosest(vector<string>& words, string word1, string word2) {
        for(int ix = 0; ix != words.size(); ++ix){
            wordpos[words[ix]].push_back(ix);
        }

        return getDistance(word1, word2);
    }

    int getDistance(const string& word1, const string& word2){
        vector<int> pos1 = wordpos[word1], pos2 = wordpos[word2];
        int ix = 0, jx = 0, curr, ret = MAX;

        while(ix < pos1.size() && jx < pos2.size()){
            curr = abs(pos1[ix] - pos2[jx]);
            if(curr < ret) ret = curr;
            if(pos1[ix] < pos2[jx]) ++ix;
            else ++jx;
        }

        return ret;
    }
};
