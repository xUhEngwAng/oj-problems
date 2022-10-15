#include <vector>
using std::vector;

/*
 * 使用单调栈的典型题，存储单调递增的柱子高度。当右边出现
 * 更低的柱子时，将栈顶弹出，其右边界就是更低的柱子元素，
 * 而左边界则为在栈中处于其左边的元素，这样可以一次循环就
 * 得到答案。
 */

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        vector<int> st;
        int left, right, curr, ret = 0;
        heights.push_back(0);

        for(int ix = 0; ix != heights.size(); ++ix){
            while(!st.empty() && heights[ix] <= heights[st.back()]){
                curr = heights[st.back()];
                st.pop_back();
                left = st.empty()? -1: st.back();
                right = ix;
                curr = curr * (right - left - 1);
                if(ret < curr) ret = curr;
            }
            st.push_back(ix);
        }

        heights.pop_back();
        return ret;
    }
};
