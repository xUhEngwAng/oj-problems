class Solution {
public:
    int search(const vector<int>& vec, int start, int end, int target){
        int lo = start, hi = end, mid;
        while(lo < hi){
            mid = (lo + hi) >> 1;
            if(vec.at(mid) < target) lo = mid + 1;
            else hi = mid;
        }
        return lo;
    }
    
    vector<int> findElement(vector<vector<int>> mat, int n, int m, int x) {
        // write code here
        /*
        int pos = m;
        for(int ix = 0; ix != n; ++ix){
            pos = search(mat.at(ix), 0, pos, x);
            if(pos < m && mat[ix][pos] == x)
                return vector<int>({ix, pos});
        }
        return vector<int>({-1, -1});
        */
        int row = n - 1, col = 0;
        while(true){
            if(mat[row][col] < x) col += 1;
            else if(mat[row][col] > x) row -= 1;
            else break;
        }
        return vector<int>({row, col});
    }
};
