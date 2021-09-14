#define INF (0x7FFFFFFF)
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 返回最小的花费代价使得这n户人家连接起来
     * @param n int n户人家的村庄
     * @param m int m条路
     * @param cost intvector<vector<>> 一维3个参数，表示连接1个村庄到另外1个村庄的花费的代价
     * @return int
     */
    int miniSpanningTree(int n, int m, vector<vector<int>>& cost) {
        // write code here
        vector<vector<pair<int, int>>> graph;
        graph.resize(n + 1);
        int start, end, len, min, ret = 0;
        for(auto entry : cost){
            start = entry[0];
            end   = entry[1];
            len   = entry[2];
            graph[start].push_back({end, len});
            graph[end].push_back({start, len});
        }
        vector<int> dist(n + 1, INF);
        vector<bool> visited(n + 1, false);
        dist[1] = 0;
        while(true){
            start = -1, min = INF;
            for(int ix = 1; ix <= n; ++ix){
                if(!visited[ix] && dist[ix] < min){
                    min = dist[ix];
                    start = ix;
                }
            }
            if(start == -1) break;   
            visited[start] = true;
            ret += dist[start];
            for(auto entry : graph[start]){
                end = entry.first;
                len = entry.second;
                if(len < dist[end]) dist[end] = len;
            }
        }
        return ret;
    }
};
