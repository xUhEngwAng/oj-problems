/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
class Solution {
public:
    pair<TreeNode*, TreeNode*> InOrder(TreeNode* root){
        if(!root) return {nullptr, nullptr};
        pair<TreeNode*, TreeNode*> left, right;
        left = InOrder(root->left);
        right = InOrder(root->right);
        
        TreeNode *head, *tail;
        head = tail = root;
        
        if(left.second){
            left.second->right = root;
            head = left.first;
        }
        root->left = left.second;
        root->right = right.first;
        if(right.first){
            right.first->left = root;
            tail = right.second;
        }
        return {head, tail};
    }
    
    TreeNode* Convert(TreeNode* pRootOfTree) {
        pair<TreeNode*, TreeNode*> res = InOrder(pRootOfTree);
        return res.first;
    }
};
