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
    vector<vector<int>> levelOrder(TreeNode* root) {
        // write code here
        int currcnt = 1, nextcnt = 0;
        TreeNode *curr;
        vector<vector<int>> ret;
        if(root == nullptr) return ret;
        vector<int> temp;
        queue<TreeNode*> q;
        q.push(root);
        
        while(!q.empty()){
            curr = q.front();
            q.pop();
            
            if(curr->left){
                q.push(curr->left);
                nextcnt += 1;
            }
            if(curr->right){
                q.push(curr->right);
                nextcnt += 1;
            }
            
            temp.push_back(curr->val);
            if(--currcnt == 0){
                ret.push_back(temp);
                temp.clear();
                currcnt = nextcnt;
                nextcnt = 0;
            }
        }
        
        return ret;
    }
};