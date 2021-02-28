/**
 * struct TreeNode {
 *	int val;
 *	struct TreeNode *left;
 *	struct TreeNode *right;
 * };
 */

class Solution {
public:
    bool findPath(TreeNode* root, int key, vector<TreeNode*>& path){
        path.push_back(root);
        
        if(!root) goto fail;
        if(root->val == key) return true;
        
        if(findPath(root->left, key, path))  return true;
        if(findPath(root->right, key, path)) return true;
        
        fail:
        path.pop_back();
        return false;
    }
    
    TreeNode* CommonAncestor(TreeNode *root, int o1, int o2){
        if(!root) return nullptr;
        if(root->val == o1 || root->val == o2) return root;
        TreeNode *left  = CommonAncestor(root->left,  o1, o2);
        TreeNode *right = CommonAncestor(root->right, o1, o2);
        if(!left)  return right;
        if(!right) return left;
        return root;
    }
    
    /**
     * 
     * @param root TreeNode类 
     * @param o1 int整型 
     * @param o2 int整型 
     * @return int整型
     */
    int lowestCommonAncestor(TreeNode* root, int o1, int o2) {
        // best solution: O(n) and O(1)
        return CommonAncestor(root, o1, o2)->val;
        
        // my solution: O(n) and O(n)
        /*vector<TreeNode*> path1, path2;
        findPath(root, o1, path1);
        findPath(root, o2, path2);
        
        for(int ix = 0, jx = 0; ix != path1.size() && jx != path2.size(); ++ix, ++jx){
            //assert(path1[ix] == path2[jx])
            if(ix == path1.size() - 1) return path1.back()->val;
            if(jx == path2.size() - 1) return path2.back()->val;
            if(path1[ix + 1] != path2[ix + 1])
                return path1[ix]->val;
        }
        
        return -1;//this should not happen
        */
    }
};