class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        // solution based on monotonic stack, O(n) and O(n)
        stack<int> s;
        vector<int> ret(T.size(), 0);

        for(int ix = 0; ix != T.size(); ++ix){

            while(!s.empty() && T[s.top()] < T[ix]){
                ret[s.top()] = ix - s.top();
                s.pop();
            }

            s.push(ix);
        }

        return ret;

        // solution based on dynamic programming, or kmp -- O(n) and O(1)
        /*
        vector<int> ret(T.size(), 0);
        int candidate;

        for(int ix = T.size() - 2; ix >= 0; --ix){
            candidate = ix + 1;

            while(true){
                if(T[ix] < T[candidate]){
                    ret[ix] = candidate - ix;
                    break;
                }
                if(ret[candidate] == 0){
                    ret[ix] = 0;
                    break;
                }
                candidate = candidate + ret[candidate];         
            }
        }

        return ret;
        */
    }
};