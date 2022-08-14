class Solution {
public:
    int m, n;

    bool exist(vector<vector<char>>& board, string word) {
        m = board.size() - 1;
        n = board[0].size() - 1;
        
        for(int ix = 0; ix <= m; ++ix)
            for(int jx = 0; jx <= n; ++jx)
                if(dfs(board, ix, jx, word, 0))
                    return true;

        return false;
    }

    bool dfs(vector<vector<char>> &board, int row, int col, string& word, int pos){
        if(board[row][col] != word[pos]) return false;
        board[row][col] = '-';

        if(pos == word.length() - 1) return true;
        if(0 < row && dfs(board, row-1, col, word, pos+1)) return true;
        if(row < m && dfs(board, row+1, col, word, pos+1)) return true;
        if(0 < col && dfs(board, row, col-1, word, pos+1)) return true;
        if(col < n && dfs(board, row, col+1, word, pos+1)) return true;

        board[row][col] = word[pos];
        return false;
    }
};
