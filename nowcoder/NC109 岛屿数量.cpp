class Solution {
public:
    /**
     * 判断岛屿数量
     * @param grid char字符型vector<vector<>> 
     * @return int整型
     */
    vector<vector<bool>> visited;
    int m, n;
    
    void dfs(vector<vector<char>>& grid, int row, int col){
        visited[row][col] = true;
        if(row > 0 && grid[row-1][col]=='1' && !visited[row-1][col]) 
            dfs(grid, row-1, col);
        if(row < m-1 && grid[row+1][col]=='1' && !visited[row+1][col]) 
            dfs(grid, row+1, col);
        if(col > 0 && grid[row][col-1]=='1' && !visited[row][col-1]) 
            dfs(grid, row, col-1);
        if(col < n-1 && grid[row][col+1]=='1' && !visited[row][col+1]) 
            dfs(grid, row, col+1);
    }
    
    int solve(vector<vector<char>>& grid) {
        // write code here
        m = grid.size();
        n = grid[0].size();
        visited.resize(m, vector<bool>(n, false));
        int cnt = 0;
        
        for(int ix = 0; ix != m; ++ix){
            for(int jx = 0; jx != n; ++jx){
                if(grid[ix][jx]=='1' && !visited[ix][jx]){
                    dfs(grid, ix, jx);
                    cnt += 1;
                }
            }
        }
        
        return cnt;
    }
};
