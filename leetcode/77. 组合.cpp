#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> ret;
    vector<int> seq;

    vector<vector<int>> combine(int n, int k) {
        for(int ix = 1; ix <= n-k+1; ++ix)
            dfs(n, k, ix);
        return ret;
    }

    void dfs(int n, int k, int curr){
        seq.push_back(curr);

        if(seq.size() == k) ret.push_back(seq);
        else
        while(++curr + k - seq.size() - 1 <= n) dfs(n, k, curr);

        seq.pop_back();
    }
};
