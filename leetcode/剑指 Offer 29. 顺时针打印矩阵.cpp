class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ret;
        int m = matrix.size();
        if(m == 0) return ret;
        int n = matrix[0].size();
        if(n == 0) return ret;

        for(int ix = 0; (ix < (m+1) >> 1) && (ix < (n+1) >> 1); ++ix){
            int top = ix, bottom = m - ix - 1;
            int left = ix, right = n - ix - 1;

            for(int jx = left; jx <= right; ++jx) ret.push_back(matrix[top][jx]);
            for(int jx = top+1; jx <= bottom; ++jx) ret.push_back(matrix[jx][right]);
            if(bottom == top || left == right) continue;
            for(int jx = right-1; jx >= left; --jx) ret.push_back(matrix[bottom][jx]);
            for(int jx = bottom-1; jx > top; --jx) ret.push_back(matrix[jx][left]);
        }

        return ret;
    }
};
