#include <stack>
#include <vector>
using std::stack;
using std::vector;

/*
 * 这个题我觉得还挺难的，似乎是某一年 hulu 的笔试题吧。它的基本思路
 * 是计算每一个 arr[ix] 在最终结果中的出现次数，为此需要计算以它为
 * 最小值的子数组的左边界与右边界，这里是使用了一个单调栈来进行这样
 * 计算。
 *
 * 单调栈维护了所有元素的索引，这些元素是单调增加的。对于其中的每一
 * 元素，其左边的元素即为它的左边界。对于数组中的每一个元素，如果它
 * 大于栈顶元素，则直接入栈，否则栈顶元素已经遇到了它的右边界，弹出
 * 栈顶元素并计算它的最终结果中的值。由于只需要对数组进行一次遍历，
 * 算法的时间复杂度是 O(n)。
 *
 * 我一开始的思路甚至没想到对每个元素计算出现次数，而是暴力枚举了所
 * 有连续子数组，时间复杂度为 O(n^2)，不出所料地超时了。
 */

class Solution {
public:
    const int MOD = 1000000007;

    int sumSubarrayMins(vector<int>& arr) {
        arr.push_back(0);
        int n = arr.size(), ret = 0, top;
        long long curr;
        stack<int> s;
        s.push(-1);

        for(int ix = 0; ix != n; ++ix){
            while(1 < s.size() && arr[ix] < arr[s.top()]){
                top = s.top();
                s.pop();
                curr = ((long long)arr[top] * (top - s.top()) * (ix - top)) % MOD;
                ret = (ret + curr) % MOD;
            }
            s.push(ix);
        }

        arr.pop_back();
        return ret;
    }
};
