#include <unordered_map>
#define MAX(X, Y) ((X) > (Y)? (X): (Y))
#define INF (0x7fffffff)

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
     * @return int整型
     */
    struct property{
        int left_value;
        int right_value;
    };
    
    unordered_map<TreeNode*, property> properties;
    int max;
    
    int get_max_value(TreeNode *node){
        int left  = properties[node].left_value;
        int right = properties[node].right_value;
        int ret = MAX(left, right);
        if(ret < 0) return 0;
        return ret;
    }
    
    void postOrder(TreeNode *root){
        int left_value = root->val, right_value = root->val, total;
        if(root->left){
            postOrder(root->left);
            left_value += get_max_value(root->left);
        }
        if(root->right){
            postOrder(root->right);
            right_value += get_max_value(root->right);
        }
        total = left_value + right_value - root->val;
        
        properties[root].left_value  = left_value;
        properties[root].right_value = right_value;
        
        if(max < total) max = total;
    }
    
    int maxPathSum(TreeNode* root) {
        // write code here
        max = -INF;
        postOrder(root);
        return max;
    }
};
