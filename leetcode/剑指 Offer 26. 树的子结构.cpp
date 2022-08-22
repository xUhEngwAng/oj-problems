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
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if(!B) return false;
        if(isSubTree(A, B)) return true;
        if(A->left &&  isSubStructure(A->left, B))  return true;
        if(A->right && isSubStructure(A->right, B)) return true;
        return false;
    }

    bool isSubTree(TreeNode* a, TreeNode* b){
        if(!a) return false;
        if(a->val != b->val) return false;
        if(b->left  && !isSubTree(a->left, b->left))   return false;
        if(b->right && !isSubTree(a->right, b->right)) return false;
        return true;
    }
};
