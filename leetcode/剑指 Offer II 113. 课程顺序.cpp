#include <queue>
#include <vector>
using std::queue;
using std::vector;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> inDegree(numCourses, 0), seq;
        vector<vector<int>> graph(numCourses);

        for(auto entry : prerequisites){
            graph[entry[1]].push_back(entry[0]);
            inDegree[entry[0]] += 1;
        }

        queue<int> q;

        for(int ix = 0; ix != numCourses; ++ix){
            if(inDegree[ix] == 0)
                q.push(ix);
        }

        while(!q.empty()){
            int curr = q.front();
            q.pop();
            seq.push_back(curr);

            for(auto neighbor : graph[curr]){
                if(--inDegree[neighbor] == 0)
                    q.push(neighbor);
            }
        }

        if(seq.size() != numCourses) seq.clear();
        return seq;
    }
};
