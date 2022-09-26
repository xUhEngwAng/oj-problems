/*
 * 这个题还蛮有意思。主要是有两种解法，即更偏向于时间和空间的解法。
 *
 * 偏向时间的解法方面，直接的想法是使用一个队列维护所有叶子节点，
 * 每次插入都插入到队列的头部。显然每次插入的时间复杂度为 O(1)，
 * 缺点是队列的空间复杂度为 O(n)。
 *
 * 此外，还有一个利用完全二叉树性质的解法。完全二叉树可以直接使用
 * 数组来表示，对于一个节点 x，其左子和右子分别为 2x 和 2x+1。因
 * 此可以在显式维护树结构以外，再维护一个包含所有节点的数组，下标
 * 为节点的索引。通过完全二叉树的性质可以在 O(1) 时间找到新插入节
 * 点的父节点。然而，这种方法的空间复杂度也是 O(n)，因为需要维护
 * 包含所有节点指针的数组。（我之前还觉得空间是 O(1)
 *
 * 偏向空间的解法即不使用额外的空间，每次在插入时再去树中寻找待插
 * 入节点的父节点。这里依然可以利用 CBT 的性质，设想一个节点的索引
 * 是 x，那么其父节点为 x >> 1，x 的最低位决定它是父节点的左子还是
 * 右子。可以通过这种方法不断向上找父节点，直到父节点为 1，即根节
 * 点。
 *
 * 反过来，我们可以先找到 x 最高为 1 的一位，对应了根节点，随后根
 * 据低位的取值，决定向树的左子还是右子移动，直到遍历完 x 的最低位。
 * 这样一次插入的空间复杂度为 O(1)，而时间复杂度为 O(logn)。
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
class CBTInserter {
public:
    int cnt = 0;
    TreeNode* r;

    CBTInserter(TreeNode* root) {
        cnt = dfs(root);
        r = root;
    }

    int dfs(TreeNode* root){
        int left = 0, right = 0;
        if(root->left) left = dfs(root->left);
        if(root->right) right = dfs(root->right);
        return left + right + 1;
    }
    
    int insert(int val) {
        cnt += 1;
        int pos = 30;
        while(!(cnt & (1 << pos--)));
        TreeNode *curr = get_root();

        for(; pos >= 1; --pos){
            if(cnt & (1 << pos)) curr = curr->right;
            else curr = curr->left;
        }

        if(!curr->left) curr->left = new TreeNode(val);
        else curr->right = new TreeNode(val);

        return curr->val;
    }
    
    TreeNode* get_root() {
        return r;
    }
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(val);
 * TreeNode* param_2 = obj->get_root();
 */
