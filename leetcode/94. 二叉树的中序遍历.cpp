#include <stack>
#include <vector>
using std::stack;
using std::vector;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(): val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ret;
        stack<TreeNode*> s;
        TreeNode* curr = root;

        while(true){
            if(!curr){
                if(s.empty()) break;
                curr = s.top();
                s.pop();
                ret.push_back(curr->val);
                curr = curr->right;
            }else{
                s.push(curr);
                curr = curr->left;
            }
        }

        return ret;
    }
};
