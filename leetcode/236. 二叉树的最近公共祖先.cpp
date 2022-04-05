/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root) return nullptr;

        vector<TreeNode*> p_anc, q_anc;
        dfs(root, p, p_anc);
        dfs(root, q, q_anc);
        int ix = 0;
        while(ix != p_anc.size() && ix != q_anc.size() && p_anc[ix] == q_anc[ix]) ++ix;
        return p_anc[ix-1];
    }

    bool dfs(TreeNode* root, TreeNode* target, vector<TreeNode*> &path){
        path.push_back(root);

        if(root == target) return true;

        if(root->left  && dfs(root->left, target, path)) return true;
        if(root->right && dfs(root->right, target, path)) return true;

        path.pop_back();
        return false;
    }
};
