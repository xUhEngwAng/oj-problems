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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return _buildTree(preorder, 0, inorder, 0, preorder.size());
    }

    TreeNode* _buildTree(vector<int>& preorder, int pre_start, vector<int>& inorder, int in_start, int length){
        if(length == 0) return nullptr;
        TreeNode* root = new TreeNode(preorder[pre_start]);
        int leftlen = 0;
        
        for(; leftlen != length; ++leftlen){
            if(inorder[leftlen + in_start] == root->val) break;
        }

        root->left  = _buildTree(preorder, pre_start+1, inorder, in_start, leftlen);
        root->right = _buildTree(preorder, pre_start+leftlen+1, inorder, in_start+leftlen+1, length-leftlen-1);
        return root;
    }
};
