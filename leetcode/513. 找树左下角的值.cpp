/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        int maxdepth, ret;
        dfs(root, maxdepth, ret);
        return ret;
    }

    void dfs(TreeNode* root, int& maxdepth, int& value){
        int ldepth = 0, rdepth = 0, lvalue = root->val, rvalue = root->val;
        if(root->left) dfs(root->left, ldepth, lvalue);
        if(root->right) dfs(root->right, rdepth, rvalue);
        value = (ldepth < rdepth)? rvalue: lvalue;
        maxdepth = (ldepth < rdepth)? rdepth: ldepth;
        maxdepth += 1;
    }
};
