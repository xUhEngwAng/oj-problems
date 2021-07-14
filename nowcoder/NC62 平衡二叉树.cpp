#include <unordered_map>
#define MAX(X, Y) ((X) > (Y)? (X): (Y))

class Solution {
public:
    unordered_map<TreeNode*, int> height;
    
    bool isBalanced(TreeNode* root){
        if(!root) return true;
        
        bool left_balanced  = isBalanced(root->left);
        bool right_balanced = isBalanced(root->right);
        int left_height = root->left? height[root->left]: 0;
        int right_height = root->right? height[root->right]: 0;
        
        if(!left_balanced || !right_balanced) return false;
        if(abs(left_height - right_height) > 1) return false;
        height[root] = MAX(left_height, right_height) + 1;
        return true;
    }
    
    bool IsBalanced_Solution(TreeNode* pRoot) {
        return isBalanced(pRoot);
    }
};
