class Solution {
public:
    int oddCells(int m, int n, vector<vector<int>>& indices) {
        vector<int> unq_rows(m, 0), unq_cols(n, 0);

        for(auto coord : indices){
            unq_rows[coord[0]] += 1;
            unq_cols[coord[1]] += 1;
        }

        int row_cnt = 0, col_cnt = 0;

        for(int ix = 0; ix != m; ++ix){
            row_cnt += unq_rows[ix] & 1;
        }

        for(int ix = 0; ix != n; ++ix){
            col_cnt += unq_cols[ix] & 1;
        }

        return n * row_cnt + m * col_cnt - 2 * row_cnt * col_cnt;
    }
};
