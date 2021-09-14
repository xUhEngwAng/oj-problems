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
     * @param root TreeNode类 the root
     * @return int整型vector
     */
    vector<int> in_order;
    
    void inOrder(TreeNode *root){
        if(!root) return;
        inOrder(root->left);
        in_order.push_back(root->val);
        inOrder(root->right);
    }
    
    vector<int> findError(TreeNode* root) {
        // write code here
        inOrder(root);
        vector<int> ret(2);
        for(int ix = 0;; ++ix){
            if(in_order[ix] > in_order[ix+1]){
                ret[1] = in_order[ix];
                break;
            }
        }
        for(int ix = in_order.size() - 1;; --ix){
            if(in_order[ix] < in_order[ix - 1]){
                ret[0] = in_order[ix];
                break;
            }
        }
        return ret;
    }
};
