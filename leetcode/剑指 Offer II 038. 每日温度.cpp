#include <vector>
using std::vector;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size(), top;
        vector<int> st, ret(n);

        for(int ix = 0; ix != n; ++ix){
            while(!st.empty() && temperatures[st.back()] < temperatures[ix]){
                top = st.back();
                st.pop_back();
                ret[top] = ix - top;
            }
            st.push_back(ix);
        }

        while(!st.empty()){
            top = st.back();
            st.pop_back();
            ret[top] = 0;
        }
        
        return ret;
    }
};
