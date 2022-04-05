#include <vector>
using std::vector;

class Solution {
public:
    vector<vector<bool>> visited;
    int m, n;

    int numIslands(vector<vector<char>>& grid) {
        m = grid.size(), n = grid[0].size();
        visited.resize(m, vector<bool>(n, false));
        int ret = 0;

        for(int ix = 0; ix != m; ++ix){
            for(int jx = 0; jx != n; ++jx){
                if(grid[ix][jx] == '1' && !visited[ix][jx]){
                    dfs(grid, ix, jx);
                    ret += 1;
                }
            }
        }

        return ret;
    }

    void dfs(vector<vector<char>> &grid, int row, int col){
        visited[row][col] = true;

        if(0 < row && grid[row-1][col] == '1' && !visited[row-1][col]) dfs(grid, row-1, col);
        if(row < m-1 && grid[row+1][col] == '1' && !visited[row+1][col]) dfs(grid, row+1, col);
        if(0 < col && grid[row][col-1] == '1' && !visited[row][col-1]) dfs(grid, row, col-1);
        if(col < n-1 && grid[row][col+1] == '1' && !visited[row][col+1]) dfs(grid, row, col+1);
    }
};
