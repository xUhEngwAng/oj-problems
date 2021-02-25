/**
 * struct TreeNode {
 *	int val;
 *	struct TreeNode *left;
 *	struct TreeNode *right;
 * };
 */

class Solution {
public:
    vector<int> pre, in, post;
    
    void PreOrder(TreeNode* root){
        if(root == nullptr) return;
        pre.push_back(root->val);
        PreOrder(root->left);
        PreOrder(root->right);
    }
    
    void InOrder(TreeNode* root){
        if(root == nullptr) return;
        InOrder(root->left);
        in.push_back(root->val);
        InOrder(root->right);
    }
    
    void PostOrder(TreeNode* root){
        if(root == nullptr) return;
        PostOrder(root->left);
        PostOrder(root->right);
        post.push_back(root->val);
    }
    
    void dfs(TreeNode* root){
        if(root == nullptr) return;
        
        pre.push_back(root->val);
        dfs(root->left);
        in.push_back(root->val);
        dfs(root->right);
        post.push_back(root->val);
    }
    
    /**
     * 
     * @param root TreeNode类 the root of binary tree
     * @return int整型vector<vector<>>
     */
    vector<vector<int>> threeOrders(TreeNode* root) {
        // write code here
        vector<vector<int>> ret;
        
        // advanced solution: one-shot dfs
        dfs(root);
        
        // naive solution: three pass traversal
        /*
        PreOrder(root);
        InOrder(root);
        PostOrder(root);
        */
        
        ret.push_back(pre);
        ret.push_back(in);
        ret.push_back(post);
        return ret;
    }
};