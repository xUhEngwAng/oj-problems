class Solution {
public:
    int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
        int ret = 0, curr, elapsed;
        vector<vector<int>> employees(n);
        for(int ix = 0; ix != n; ++ix){
            if(manager[ix] == -1) continue;
            employees[manager[ix]].push_back(ix);
        }

        queue<pair<int, int>> q;
        q.push({headID, 0});
        while(!q.empty()){
            auto tmp = q.front();
            q.pop();
            curr = tmp.first, elapsed = tmp.second;
            if(ret < elapsed) ret = elapsed;
            for(auto e : employees[curr]){
                q.push({e, elapsed+informTime[curr]});
            }
        }

        return ret;
    }
};
