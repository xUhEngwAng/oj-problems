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
    const int INF = (0x7fffffff);
    vector<int> ret;

    void inOrder(TreeNode* root, vector<int>& res){
        if(!root) return;
        inOrder(root->left, res);
        res.push_back(root->val);
        inOrder(root->right, res);
    }

    vector<int>& merge(const vector<int>& l1, const vector<int>& l2){
        int lh, rh;
        ret.clear();
        for(int ix = 0, jx = 0; ix != l1.size() || jx != l2.size();){
            lh = (ix == l1.size()? INF: l1[ix]);
            rh = (jx == l2.size()? INF: l2[jx]);
            if(lh < rh) {
                ret.push_back(lh);
                ix += 1;
            }else{
                ret.push_back(rh);
                jx += 1;
            }
        }
        return ret;
    }
    
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        vector<int> l1, l2;
        inOrder(root1, l1);
        inOrder(root2, l2);
        return merge(l1, l2);
    }
};
