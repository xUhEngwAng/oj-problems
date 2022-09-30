#include <algorithm>
#include <vector>
using std::vector;
using std::reverse;

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
    vector<vector<int>> pathSum(TreeNode* root, int target) {
        if(!root) return vector<vector<int>>();
        vector<vector<int>> ret = _pathSum(root, target);
        
        for(int ix = 0; ix != ret.size(); ++ix)
            reverse(ret[ix].begin(), ret[ix].end());

        return ret;
    }

    vector<vector<int>> _pathSum(TreeNode* root, int target){
        vector<vector<int>> left, right;
        target = target - root->val;
        if(target == 0 && !root->left && !root->right){
            left.resize(1, vector<int>(1, root->val));
            return left;
        }
        if(root->left) left = _pathSum(root->left, target);
        if(root->right) right = _pathSum(root->right, target);

        for(int ix = 0; ix != left.size(); ++ix)
            left[ix].push_back(root->val);
        for(int ix = 0; ix != right.size(); ++ix)
            right[ix].push_back(root->val);

        if(left.empty()) return right;
        for(auto path : right)
            left.push_back(path);
        return left;
    }
};
