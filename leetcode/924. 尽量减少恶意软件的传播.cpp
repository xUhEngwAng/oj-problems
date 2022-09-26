#include <vector>
using namespace std;

class Solution {
public:
    vector<int> connectedBy;
    vector<vector<int>> adjacent_table;

    int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
        int n = graph.size(), src, ret, max = -1;
        connectedBy.resize(n, -1);
        adjacent_table.resize(n);
        for(int ix = 0; ix != n; ++ix){
            for(int jx = ix+1; jx != n; ++jx){
                if(graph[ix][jx]){
                    adjacent_table[ix].push_back(jx);
                    adjacent_table[jx].push_back(ix);
                }
            }
        }

        vector<int> candidates(n); 
        for(auto e : initial){
            if(connectedBy[e] != -1){
                src = connectedBy[e];
                candidates[src] = 0;
                continue;
            }
            candidates[e] = dfs(e, e);
        }

        for(auto e : initial){
            if(max < candidates[e]){
                max = candidates[e];
                ret = e;
            }else
            if(max == candidates[e] && e < ret)
                ret = e;
        }

        return ret;
    }

    int dfs(int src, int curr){
        int ret = 1;
        connectedBy[curr] = src;
        for(auto neighbor : adjacent_table[curr]){
            if(connectedBy[neighbor] != -1) continue;
            ret += dfs(src, neighbor);
        }

        return ret;
    }
};
