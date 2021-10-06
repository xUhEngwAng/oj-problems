class Solution {
public:
    struct TreeNode{
        char val;
        vector<TreeNode*> children;
        TreeNode(char ch){
            val = ch;
            children.resize(26, nullptr);
        }
    };

    TreeNode* trie;
    vector<vector<bool>> visited;
    int m, n;

    void dfs(vector<vector<char>>& board, int row, int col, TreeNode* root, int depth){
        if(depth == 10) return;
        visited[row][col] = true;
        char curr = board[row][col];
        if(!root->children[curr-'a'])
            root->children[curr-'a'] = new TreeNode(curr);
        root = root->children[curr-'a'];
        if(row > 0 && !visited[row-1][col])
            dfs(board, row-1, col, root, depth+1);
        if(row < m-1 && !visited[row+1][col])
            dfs(board, row+1, col, root, depth+1);
        if(col > 0 && !visited[row][col-1])
            dfs(board, row, col-1, root, depth+1);
        if(col < n-1 && !visited[row][col+1])
            dfs(board, row, col+1, root, depth+1);
        visited[row][col] = false;
    }

    void buildTrie(vector<vector<char>>& board){
        trie = new TreeNode('/');
        m = board.size(), n = board[0].size();
        visited.resize(m, vector<bool>(n, false));
        for(int ix = 0; ix != m; ++ix)
        for(int jx = 0; jx != n; ++jx){
            dfs(board, ix, jx, trie, 0);
        }
    }

    bool findWord(const string& word){
        TreeNode *curr = trie;
        for(auto ch : word){
            curr = curr->children[ch-'a'];
            if(!curr) return false;
        }
        return true;
    }

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        buildTrie(board);
        vector<string> ret;
        for(auto word : words){
            if(findWord(word))
                ret.push_back(word);
        }
        return ret;
    }
};
