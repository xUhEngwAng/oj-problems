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
    int maxLevelSum(TreeNode* root) {
        queue<TreeNode*> *curr = new queue<TreeNode*>(), *next = new queue<TreeNode*>();
        int currsum = 0, maxsum = 0x80000000, currlayer = 1, maxlayer;
        curr->push(root);

        while(!curr->empty()){
            TreeNode* node = curr->front();
            curr->pop();
            currsum += node->val;
            if(node->left) next->push(node->left);
            if(node->right) next->push(node->right);
            if(curr->empty()){
                curr = next;
                next = new queue<TreeNode*>();
                if(maxsum < currsum){
                    maxsum = currsum;
                    maxlayer = currlayer;
                }
                currlayer += 1;
                currsum = 0;
            }
        }

        return maxlayer;
    }
};
