#include <vector>
using std::vector;

class Solution {
public:
    int n;
    vector<bool> visited;

    void dfs(const vector<vector<int>>& isConnected, int curr){
        visited[curr] = true;

        for(int ix = 0; ix != n; ++ix){
            if(!visited[ix] && isConnected[curr][ix])
                dfs(isConnected, ix);
        }
    }

    int findCircleNum(vector<vector<int>>& isConnected) {
        n = isConnected.size();
        visited.resize(n, false);
        int ret = 0;

        for(int ix = 0; ix != n; ++ix){
            if(visited[ix]) continue;
            dfs(isConnected, ix);
            ret += 1;
        }

        return ret;
    }
};
