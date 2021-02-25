/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

typedef vector<int>::iterator iter;

class Solution {
public:
    TreeNode* reconstruct(iter pre1, iter pre2, iter in1, iter in2){
        if(pre1 == pre2) return NULL;

        int length;

        for(length = 0; in1 + length != in2; ++length)
            if(*(in1 + length) == *pre1) break;
        
        TreeNode* root  = new TreeNode(*pre1);
        TreeNode* left  = reconstruct(pre1 + 1, pre1 + 1 + length, in1, in1 + length);
        TreeNode* right = reconstruct(pre1 + 1 + length, pre2, in1 + length + 1, in2);
        root->left  = left;
        root->right = right;
        return root;
    }


    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        return reconstruct(pre.begin(), pre.end(), vin.begin(), vin.end());
    }
};