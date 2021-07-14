class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 求二叉树的右视图
     * @param xianxu int整型vector 先序遍历
     * @param zhongxu int整型vector 中序遍历
     * @return int整型vector
     */
    typedef vector<int>::iterator iter;
    
    struct TreeNode{
        int val;
        TreeNode* left;
        TreeNode* right;
    };
    
    TreeNode* restore(iter pre_begin, iter in_begin, int length){
        if(length == 0) return nullptr;
        
        TreeNode* ret = new TreeNode();
        ret->val = *pre_begin;
        int ix;
        for(ix = 0; ix != length; ++ix){
            if(*(in_begin + ix) == *pre_begin) 
                break;
        }
        ret->left  = restore(pre_begin+1, in_begin, ix);
        ret->right = restore(pre_begin+ix+1, in_begin+ix+1, length-ix-1);
        return ret;
    }
    
    vector<int> solve(vector<int>& xianxu, vector<int>& zhongxu) {
        // write code here
        TreeNode* tree = restore(xianxu.begin(), zhongxu.begin(), xianxu.size());
        TreeNode* tmp;
        vector<TreeNode*> curr, next;
        vector<int> ret;
        curr.push_back(tree);
        
        while(!curr.empty()){
            for(int ix = 0; ix != curr.size(); ++ix){
                tmp = curr.at(ix);
                if(tmp->left)  next.push_back(tmp->left);
                if(tmp->right) next.push_back(tmp->right);
            }
            ret.push_back(curr.back()->val);
            curr = next;
            next.clear();
        }
        
        return ret;
    }
};
