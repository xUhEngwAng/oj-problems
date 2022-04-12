#include <string>
using std::string;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(!root) return "";

        string left_str  = "{" + serialize(root->left)  + "}";
        string right_str = "{" + serialize(root->right) + "}";
        string ret = left_str + to_string(root->val) + right_str;
        return ret;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data.empty()) return nullptr;
        int left_cnt = 0, right_cnt = 0, left_end, right_begin;

        for(left_end = 0; left_end != data.length(); ++left_end){
            if(data[left_end] == '{') left_cnt += 1;
            else 
            if(data[left_end] == '}') right_cnt += 1;
            if(left_cnt == right_cnt) break;
        }

        TreeNode* left = deserialize(data.substr(1, left_end-1));
        right_begin = data.find("{", left_end + 1);
        TreeNode* right = deserialize(data.substr(right_begin+1, data.length()-right_begin-2));
        TreeNode* root = new TreeNode();
        root->left  = left;
        root->right = right;
        root->val = stoi(data.substr(left_end+1, right_begin-left_end-1));
        return root;
    }
};
