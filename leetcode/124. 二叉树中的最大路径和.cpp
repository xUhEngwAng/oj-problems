#define MAX(X, Y) ((X)<(Y)?(Y):(X))

/*
 * 这个题我一开始超时了，经过（很大）一番检查才发现，我是写了
 * 
 * MAX(0, dfs(root->left))
 *
 * 这样的语句，宏定义展开后里面的 dfs 可以运行两遍😅
 */ 

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };


class Solution {
public:
    int max_path_sum;

    int maxPathSum(TreeNode* root) {
        max_path_sum = 0x80000000;
        dfs(root);
        return max_path_sum;
    }

    int dfs(TreeNode* root){
        int left_path = 0, right_path = 0, path_sum;

        if(root->left)  left_path  = dfs(root->left);
        if(root->right) right_path = dfs(root->right);
        left_path  = MAX(0, left_path);
        right_path = MAX(0, right_path);

        path_sum = left_path + right_path + root->val;
        if(max_path_sum < path_sum)
            max_path_sum = path_sum;

        return MAX(left_path, right_path) + root->val;
    }
};
