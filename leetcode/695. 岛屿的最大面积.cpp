#define MAX(X, Y) ((X) > (Y)? (X): (Y))

class Solution {
public:
    vector<vector<bool>> visited;
    int m, n;

    int dfs(int row, int col, const vector<vector<int>>& grid){
        visited[row][col] = true;
        int ret = 1;
        if(row > 0 && grid[row-1][col] && !visited[row-1][col])
            ret += dfs(row-1, col, grid);
        if(row < m-1 && grid[row+1][col] && !visited[row+1][col])
            ret += dfs(row+1, col, grid);
        if(col > 0 && grid[row][col-1] && !visited[row][col-1])
            ret += dfs(row, col-1, grid);
        if(col < n-1 && grid[row][col+1] && !visited[row][col+1])
            ret += dfs(row, col+1, grid);
        return ret;
    }

    int maxAreaOfIsland(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        visited.resize(m, vector<bool>(n, false));
        int max = 0, curr;
        for(int ix = 0; ix != m; ++ix){
            for(int jx = 0; jx != n; ++jx){
                if(grid[ix][jx] && !visited[ix][jx]){
                    curr = dfs(ix, jx, grid);
                    if(max < curr) max = curr;
                }
            }
        }
        return max;
    }
};
