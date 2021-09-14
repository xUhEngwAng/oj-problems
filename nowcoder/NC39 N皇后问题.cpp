class Solution {
public:
    /**
     * 
     * @param n int整型 the n
     * @return int整型
     */
    vector<pair<int, int>> positions;
    int ret = 0;
    
    bool is_violate(const pair<int, int>& lh, const pair<int, int>& rh){
        if(lh.first == rh.first || lh.second == rh.second)
            return true;
        if(lh.first - lh.second == rh.first - rh.second)
            return true;
        if(lh.first + lh.second == rh.first + rh.second)
            return true;
        return false;
    }
    
    void dfs(int row, int col, int n){
        positions.push_back({row, col});
        for(int ix = 0; ix != positions.size() - 1; ++ix){
            if(is_violate(positions[ix], positions.back()))
                goto clean;
        }
        if(row == n - 1){
            ret += 1;
            goto clean;
        }
        for(int ix = 0; ix != n; ++ix){
            dfs(row + 1, ix, n);
        }
        clean:
        positions.pop_back();
    }
    
    int Nqueen(int n) {
        // write code here
        for(int ix = 0; ix != n; ++ix)
            dfs(0, ix, n);
        return ret;
    }
};
