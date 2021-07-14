#define MAX(X, Y) ((X) > (Y)? (X): (Y))
/**
 * struct TreeNode {
 *	int val;
 *	struct TreeNode *left;
 *	struct TreeNode *right;
 * };
 */

class Solution {
public:
    /**
     * 
     * @param root TreeNode类 
     * @return int整型
     */
    int postOrder(TreeNode *root){
        int left = 0, right = 0;
        if(root->left)  left = postOrder(root->left);
        if(root->right) right = postOrder(root->right);
        return MAX(left, right) + 1;
    }
    
    int maxDepth(TreeNode* root) {
        // write code here
        if(!root) return 0;
        return postOrder(root);
    }
};
