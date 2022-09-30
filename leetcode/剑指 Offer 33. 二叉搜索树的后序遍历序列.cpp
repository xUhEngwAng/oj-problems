#include <vector>
using std::vector;

class Solution {
public:
    bool verifyPostorder(vector<int>& postorder) {
        return dfs(postorder, 0, postorder.size());
    }

    bool dfs(const vector<int>& postorder, int begin, int end){
        if(end - begin <= 1) return true;
        int split_pos = begin;
        while(split_pos < end && postorder[split_pos] < postorder[end-1]) ++split_pos;
        for(int ix = split_pos; ix < end; ++ix){
            if(postorder[ix] < postorder[end-1]) return false;
        }
        if(!dfs(postorder, begin, split_pos)) return false;
        return dfs(postorder, split_pos, end-1);
    }
};
