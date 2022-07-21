/*
 * 此题确实还是 easy 的，但是我就是想要原地返回，不借助别的空间，
 * 因此写起来多花了些时间，主要是一些细节上的处理。看了下官方题解
 * 是返回了一个新创建的 vector，也合理吧，但就没啥技术含量了（笑
 */

class Solution {
public:
    int m, n;
    const int BIAS = 2001;

    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        m = grid.size(), n = grid[0].size();
        cout << "m = " << m << ", n = " << n << endl;
        for(int ix = 0; ix != m; ++ix){
            for(int jx = 0; jx != n; ++jx){
                grid[ix][jx] -= BIAS;
            }
        }

        for(int ix = 0; ix != m; ++ix){
            for(int jx = 0; jx != n; ++jx){
                shift(grid, pair<int, int>(ix, jx), k);
            }
        }

        return grid;
    }

    void shift(vector<vector<int>>& grid, pair<int, int> start, int k){
        int temp = grid[start.first][start.second];
        if(-1000 <= temp) return;
        pair<int, int> curr = start, prev;        
        while((prev = step(curr, k)) != start){
            grid[curr.first][curr.second] = grid[prev.first][prev.second] + BIAS;
            curr = prev;
        }

        grid[curr.first][curr.second] = temp + BIAS;
    }


    pair<int, int> step(pair<int, int> curr_pos, int k){
        int row = curr_pos.first, col = curr_pos.second;
        int idx = row * n + col - k;
        while(idx < 0) idx += m * n;
        pair<int, int> ret(idx / n, idx % n);
        return ret;
    }
};
