#define MAX(X, Y) ((X)<(Y)?(Y):(X))
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
    int max_diam;

    int diameterOfBinaryTree(TreeNode* root) {
        if(!root) return 0;
        max_diam = 0;
        dfs(root);
        return max_diam;
    }

    int dfs(TreeNode* root){
        int left_length = -1, right_length = -1;
        if(root->left)  left_length  = dfs(root->left);
        if(root->right) right_length = dfs(root->right);

        int curr_diam = left_length + right_length + 2;
        if(max_diam < curr_diam) max_diam = curr_diam;
        
        return MAX(left_length, right_length) + 1;
    }
};
