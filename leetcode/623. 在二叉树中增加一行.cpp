/*
 * 这个题我是用了一个队列做 bfs，空间复杂度是 O(n)。实际上这个题可以
 * 直接用 dfs 来搜所有深度为 depth-1 的节点。最坏情况下空间复杂度仍然
 * 是 O(n)，但在树比较平衡的情况下只需要 O(logn) 的空间，应该是更优的。
 */

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
    TreeNode* addOneRow(TreeNode* root, int val, int depth) {
        if(depth == 1) return new TreeNode(val, root, nullptr);

        queue<TreeNode*> *curr = new queue<TreeNode*>(), *next = new queue<TreeNode*>();
        TreeNode* dummy = new TreeNode(-1, root, nullptr);
        int curr_depth = 1;
        curr->push(dummy);

        while(true){
            auto node = curr->front();
            curr->pop();
            if(node->left) next->push(node->left);
            if(node->right) next->push(node->right);
            if(curr->empty()){
                curr = next;
                next = new queue<TreeNode*>;
                if(++curr_depth == depth) break;
            }
        }

        while(!curr->empty()){
            auto node = curr->front();
            curr->pop();
            node->left = new TreeNode(val, node->left, nullptr);
            node->right = new TreeNode(val, nullptr, node->right);
        }

        return root;
    }
};
