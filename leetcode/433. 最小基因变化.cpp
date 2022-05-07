#include <queue>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank) {
        if(start == end) return 0;
        int n = bank.size(), curr;
        
        vector<bool> visited(n, false);
        vector<int> distances(n, -1);
        
        bank.push_back(start);
        distances.push_back(0);
        
        queue<int> q;
        q.push(n);

        while(!q.empty()){
            curr = q.front();
            q.pop();

            for(int ix = 0; ix != n; ++ix){
                if(!visited[ix] && isNeighbor(bank[curr], bank[ix])){
                    q.push(ix);
                    visited[ix] = true;
                    distances[ix] = distances[curr] + 1;
                }
            }
        }

        for(int ix = 0; ix != n; ++ix)
            if(bank[ix] == end)
                return distances[ix];
        return -1;
    }

    bool isNeighbor(const string& lhs, const string& rhs){
        int diff = 0;

        for(int ix = 0; ix != lhs.length(); ++ix){
            if(lhs[ix] == rhs[ix]) continue;
            diff++;
        }

        return diff == 1;
    }
};
