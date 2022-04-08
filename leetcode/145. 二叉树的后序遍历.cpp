#include <stack>
#include <vector>
using std::stack;
using std::vector;

/*
 * 树的后续遍历revisit。第一个版本是我自己DIY的版本，想了好久...
 * 第二个版本是回顾下邓公写的版本，思路果然清晰很多，自己又仿照
 * 着写了一遍。
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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ret;
        stack<TreeNode*> s;
        TreeNode *curr = root, *next;
        bool backtrace = false;

        while(true){
            if(!curr){
                if(s.empty()) break;
                curr = s.top();
                s.pop();
                backtrace = true;
                continue;
            }
            if(backtrace){
                ret.push_back(curr->val);
                if(s.empty()) break;
                next = s.top();
                s.pop();
                if(curr != next->left && curr != next->right)
                    backtrace = false;
                curr = next;
                continue;
            }
            s.push(curr);
            if(!curr->left) curr = curr->right;
            else{
                if(curr->right) s.push(curr->right);
                curr = curr->left;
            }
        }

        return ret;
    }

    vector<int> postOrderTraversal(TreeNode* root){
        vector<int> ret;
        stack<TreeNode*> s;
        TreeNode  *curr, *next;
        if(root) s.push(root);

        while(!s.empty()){
            next = s.top();
            if(next->left != curr && next->right != curr){
                curr = next;
                while(curr){
                    if(curr->right) s.push(curr->right);
                    if(curr->left){
                        s.push(curr->left);
                        curr = curr->left;
                    }else
                        curr = curr->right;
                }
            }
            curr = s.top();
            s.pop();
            ret.push_back(curr->val);
        }

        return ret;
    }
};
