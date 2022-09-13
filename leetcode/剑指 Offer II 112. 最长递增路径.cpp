#include <vector>
#define MAX(X, Y) ((X)<(Y)?(Y):(X))
using namespace std;

class Solution {
public:
    vector<vector<int>> longest_path;

    int pathLength(const vector<vector<int>>& matrix, int row, int col){
        if(longest_path[row][col] != -1) return longest_path[row][col];
        if(0 < row && matrix[row-1][col] < matrix[row][col])
            longest_path[row][col] = MAX(longest_path[row][col], pathLength(matrix, row-1, col)+1);
        if(row < matrix.size()-1 && matrix[row+1][col] < matrix[row][col])
            longest_path[row][col] = MAX(longest_path[row][col], pathLength(matrix, row+1, col)+1);
        if(0 < col && matrix[row][col-1] < matrix[row][col])
            longest_path[row][col] = MAX(longest_path[row][col], pathLength(matrix, row, col-1)+1);
        if(col < matrix[0].size()-1 && matrix[row][col+1] < matrix[row][col])
            longest_path[row][col] = MAX(longest_path[row][col], pathLength(matrix, row, col+1)+1);
        if(longest_path[row][col] == -1) 
            longest_path[row][col] = 1;
        return longest_path[row][col];
    }

    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int ret = 0, curr;
        longest_path.resize(matrix.size(), vector<int>(matrix[0].size(), -1));
        
        for(int ix = 0; ix != matrix.size(); ++ix){
            for(int jx = 0; jx != matrix[0].size(); ++jx){
                ret = MAX(ret, pathLength(matrix, ix, jx));
            }
        }

        return ret;
    }
};
