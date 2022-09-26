class Solution {
public:
    int smallestDifference(vector<int>& a, vector<int>& b) {
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        int ret = 0x7fffffff, ix = 0, jx = 0;
        
        while(true){
            long long curr = a[ix] - b[jx];
            if(curr < 0) { curr = -curr, ix += 1; }
            else jx += 1;
            if(curr < ret) ret = curr;
            if(ix == a.size() || jx == b.size()) break;
        }

        return ret;
    }
};
