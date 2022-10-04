#include <vector>
#define MAX(X, Y) ((X)<(Y)?(Y):(X))
using std::vector;

/*
 * 一个简单的 dp，但是我居然用了一个一维数组来保存过程中所有
 * 子状态的值。实际上状态的更新只依赖前两个状态，因此可以用
 * 滚动数组的方法来优化空间复杂度，使之只有 O(1).
 */

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        int prevprev = 0, prev = 0, curr;

        for(int ix = 0; ix != n; ++ix){
            curr = MAX(prev, prevprev + nums[ix]);
            prevprev = prev;
            prev = curr;
        }

        return curr;
    }
};
