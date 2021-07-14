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
    long long sum;
    
    void dfs(TreeNode* root, long long curr){
        curr = curr * 10 + root->val;
        if(root->left) dfs(root->left, curr);
        if(root->right) dfs(root->right, curr);
        if(!root->left && !root->right)
            sum += curr;
    }   
    
    int sumNumbers(TreeNode* root) {
        // write code here
        if(!root) return 0;
        sum = 0;
        dfs(root, 0);
        return sum;
    }
};
