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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<TreeNode*> curr, next;
        vector<vector<int>> ret;
        vector<int> layer;
        
        if(root) curr.push_back(root);
        bool should_reverse = false;
        
        while(!curr.empty()){
            for(auto node : curr){
                if(node->left)  next.push_back(node->left);
                if(node->right) next.push_back(node->right);
                layer.push_back(node->val);
            }
            
            if(should_reverse)
                reverse(layer.begin(), layer.end());
            ret.push_back(layer);
            layer.clear();
            should_reverse = should_reverse ^ 1;
            
            curr = next;
            next.clear();
        }
        
        return ret;
    }
};
