class Solution {
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        if(matrix.empty()) return false;
        int m = matrix[0].size(), n = matrix.size();
        int row = n - 1, col = 0;

        while(0 <= row && col < m){
            if(target < matrix[row][col]) row -= 1;
            else if(matrix[row][col] < target) col += 1;
            else return true;
        }

        return false;
    }
};
