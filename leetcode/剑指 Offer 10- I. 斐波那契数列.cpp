class Solution {
public:
    const int mod = 1000000007;

    int fib(int n) {
        int curr, prevprev = -1, prev = 1;

        for(int ix = 0; ix <= n; ++ix){
            curr = (prev + prevprev) % mod;
            prevprev = prev;
            prev = curr;
        }

        return curr;
    }
};
