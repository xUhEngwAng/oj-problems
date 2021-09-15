class Solution {
public:
    const int MOD = 1e9 + 7;

    int concatenatedBinary(int n) {
        long long curr = 0;
        int bias = 1;
        for(int ix = 1; ix <=n; ++ix){
            if(ix == bias) bias = bias << 1;
            curr = (curr * bias % MOD + ix) % MOD;
        }
        return curr;
    }
};
