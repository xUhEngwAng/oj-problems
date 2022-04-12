#define MIN(X, Y) ((X)<(Y)?(X):(Y))

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        vector<int> prev(matrix[0].size() + 1, 0);
        vector<int> curr(matrix[0].size() + 1, 0);
        int max = 0;

        for(int ix = 1; ix <= matrix.size(); ++ix){
            for(int jx = 1; jx <= matrix[0].size(); ++jx){
                if(matrix[ix-1][jx-1] == '0') continue;
                curr[jx] = MIN(MIN(curr[jx-1], prev[jx-1]), prev[jx]) + 1;
                if(max < curr[jx]) max = curr[jx];
            }

            prev = curr;
            curr = vector<int>(matrix[0].size() + 1, 0);
        }

        return max * max;
    }
};
