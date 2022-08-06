class Solution {
public:
    const int mod = 1000000007;

    int numWays(int n) {
        int prevprev = 1, prev = 0, curr;

        for(int ix = 0; ix <= n; ++ix){
            curr = (prev + prevprev) % mod;
            prevprev = prev;
            prev = curr;
        }

        return curr;
    }
};
