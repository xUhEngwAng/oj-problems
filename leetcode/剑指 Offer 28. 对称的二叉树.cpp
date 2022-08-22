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
    bool isSymmetric(TreeNode* root) {
        if(root == nullptr) return true;
        return isMirror(root->left, root->right);
    }

    bool isMirror(TreeNode* left, TreeNode* right){
        if(left == nullptr && right == nullptr) return true;
        if(left == nullptr || right == nullptr) return false;
        if(left->val != right->val) return false;
        return isMirror(left->left, right->right) && isMirror(left->right, right->left);
    }
};
