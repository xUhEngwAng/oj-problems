#include <vector>
#include <unordered_map>
#include <unordered_set>
#define MIN(X, Y) ((X)<(Y)?(X):(Y))
#define MAX(X, Y) ((X)<(Y)?(Y):(X))

using namespace std;

class Solution {
public:
    int size;
    unordered_map<int, unordered_set<int>> row_lamps, col_lamps, diag_lamps, rdiag_lamps;

    vector<int> gridIllumination(int n, vector<vector<int>>& lamps, vector<vector<int>>& queries) {
        size = n - 1;
        int row, col;

        for(auto lamp : lamps){
            row = lamp[0], col = lamp[1];
            row_lamps[row].insert(col);
            col_lamps[col].insert(row);
            diag_lamps[row-col+size].insert(row);
            rdiag_lamps[row+col].insert(row);
        }

        vector<int> ret;
        ret.reserve(queries.size());

        for(auto query : queries){
            row = query[0], col = query[1];
            ret.push_back(isIlluminated(row, col));
            turnoff_square(row, col);
        }

        return ret;
    }

    bool isIlluminated(int row, int col){
        if(!row_lamps[row].empty()) return true;
        if(!col_lamps[col].empty()) return true;
        if(!diag_lamps[row-col+size].empty()) return true;
        if(!rdiag_lamps[row+col].empty()) return true;
        return false;
    }

    void turnoff_square(int row, int col){
        for(int ix = MAX(row-1, 0); ix <= MIN(row+1, size); ++ix)
            for(int jx = MAX(col-1, 0); jx <= MIN(col+1, size); ++jx)
                turnoff(ix, jx);
    }

    void turnoff(int row, int col){
        row_lamps[row].erase(col);
        col_lamps[col].erase(row);
        diag_lamps[row-col+size].erase(row);
        rdiag_lamps[row+col].erase(row);
    }
};
