/*
 * 这个题我本来想的是一维的前缀和，没想到可以直接用二维前缀和写。
 * 思路其实也很不复杂，稍微一想就能想明白，为啥就是没有想到呢？
 */

class NumMatrix {
public:
    vector<vector<int>> sub_matrix_sum;
    int m, n;

    NumMatrix(vector<vector<int>>& matrix) {
        m = matrix.size(), n = matrix[0].size();
        sub_matrix_sum.resize(m+1, vector<int>(n+1, 0));

        for(int ix = 1; ix <= m; ++ix){
            for(int jx = 1; jx <= n; ++jx){
                sub_matrix_sum[ix][jx] = sub_matrix_sum[ix][jx-1] + sub_matrix_sum[ix-1][jx] - sub_matrix_sum[ix-1][jx-1] + matrix[ix-1][jx-1];
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return sub_matrix_sum[row2+1][col2+1] - sub_matrix_sum[row2+1][col1] - sub_matrix_sum[row1][col2+1] + sub_matrix_sum[row1][col1];
    }
};

class NumMatrix {
public:
    int m, n;
    vector<vector<int>> row_sum;

    NumMatrix(vector<vector<int>>& matrix) {
        m = matrix.size(), n = matrix[0].size();
        row_sum.resize(m, vector<int>(n+1, 0));

        for(int ix = 0; ix != m; ++ix){
            for(int jx = 0; jx != n; ++jx){
                row_sum[ix][jx+1] = row_sum[ix][jx] + matrix[ix][jx];
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        int ret = 0;

        for(int ix = row1; ix <= row2; ++ix){
            ret += row_sum[ix][col2+1] - row_sum[ix][col1];
        }

        return ret;
    }
};
