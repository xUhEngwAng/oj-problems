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
     * @return int整型vector<vector<>>
     */
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        // write code here
        vector<vector<int>> ret;
        TreeNode* node;
        int level = 0, size;
        
        vector<TreeNode*> curr, next;
        if(root) curr.push_back(root);
        
        while(!curr.empty()){
            size = curr.size();
            ret.push_back(vector<int>());
            ret.back().resize(size);
            
            for(int ix = 0; ix != size; ++ix){
                node = curr.at(ix);
                if(node->left)  next.push_back(node->left);
                if(node->right) next.push_back(node->right);
                if(level == 0) ret.back().at(ix) = node->val;
                else ret.back().at(size-ix-1) = node->val;
            }
           
            curr = next;
            next.clear();
            level ^= 1;
        }
        
        return ret;
    }
};
