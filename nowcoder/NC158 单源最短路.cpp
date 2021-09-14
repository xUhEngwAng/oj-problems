#define INF (0x7FFFFFFF)

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param n int 顶点数
     * @param m int 边数
     * @param graph intvector<vector<>> 一维3个数据，表示顶点到另外一个顶点的边长度是多少​
     * @return int
     */
    int findShortestPath(int n, int m, vector<vector<int>>& graph) {
        // write code here
        vector<vector<pair<int, int>>> adjacent_graph;
        adjacent_graph.resize(n + 1);
        int start, end, len, min;
        for(int ix = 0; ix != graph.size(); ++ix){
            start = graph[ix][0];
            end   = graph[ix][1];
            len   = graph[ix][2];
            adjacent_graph[start].push_back({end, len});
        }
        vector<int> dist(n + 1, INF);
        vector<bool> visited(n + 1, false);
        dist[1] = 0;
        
        while(true){
            min = INF;
            start = -1;
            for(int ix = 1; ix <= n; ++ix){
                if(!visited[ix] && dist[ix] < min){
                    min = dist[ix];
                    start = ix;
                }
            }
            if(start == -1) break;
            for(auto entry : adjacent_graph[start]){
                end = entry.first;
                len = entry.second;
                if(dist[start] + len < dist[end]) 
                    dist[end] = dist[start] + len;
            }
            visited[start] = true;
        }
        
        return (dist[n] == INF)? -1: dist[n];
    }
};
