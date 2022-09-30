/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/*
 * 这个题和 297 是完全一样的，后者我之前已经写过了，用的是括号
 * 来保存树的结构，写起来是比较容易的。这里的写法是用了层序遍历，
 * 空节点用 * 来表示，这样序列化后字符串的长度应该可以减少不少。
 * 官方题解还有个前序遍历的，思路跟我这个也差不多，但看起来还挺
 * 巧妙的。
 */

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string ret;
        queue<TreeNode*> q;
        q.push(root);
        TreeNode *curr;

        while(!q.empty()){
            curr = q.front();
            q.pop();

            if(!curr) ret.push_back('*');
            else{
                ret += to_string(curr->val);
                q.push(curr->left);
                q.push(curr->right);
            }
            ret.push_back('/');
        }

        return ret;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        TreeNode *root, *curr;
        int begin = 0, end = data.find('/', begin);
        string val = data.substr(begin, end - begin);
        if(val == "*"){
            root = nullptr;
            return root;
        }
        root = new TreeNode(stoi(val));
        curr = root;
        queue<TreeNode*> q;
        begin = end + 1;

        while(begin < data.length()){
            end = data.find('/', begin);
            val = data.substr(begin, end - begin);
            if(val == "*") curr->left = nullptr;
            else{
                curr->left = new TreeNode(stoi(val));
                q.push(curr->left);
            }

            begin = end + 1;
            end = data.find('/', begin);
            val = data.substr(begin, end - begin);
            if(val == "*") curr->right = nullptr;
            else{
                curr->right = new TreeNode(stoi(val));
                q.push(curr->right);
            }

            curr = q.front();
            q.pop();
            begin = end + 1;
        }

        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));``
