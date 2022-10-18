#include <vector>
using std::vector;

class Solution {
public:
    vector<int> constructArr(vector<int>& a) {
        if(a.empty()) return vector<int>();
        
        int n = a.size(), prod = 1;
        vector<int> ret(a.size(), 1);

        for(int ix = 1; ix != n; ++ix){
            prod = prod * a[ix-1];
            ret[ix] = ret[ix] * prod;
        }

        prod = 1;

        for(int ix = n-2; ix >= 0; --ix){
            prod = prod * a[ix+1];
            ret[ix] = ret[ix] * prod;
        }

        return ret;
    }
};
