class Solution {
public:
    vector<int> printNumbers(int n) {
        int target = pow(10, n)-1;
        vector<int> ret;
        ret.reserve(target);

        for(int ix = 1; ix <= target; ++ix)
            ret.push_back(ix);

        return ret;
    }
};
