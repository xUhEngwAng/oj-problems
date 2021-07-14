class Solution {
public:
    int Fibonacci(int n) {
        int curr = 0, prev = 0, prevPrev = 1;
        for(int ix = 0; ix < n; ++ix){
            curr = prevPrev + prev;
            prevPrev = prev;
            prev = curr;
        }
        return curr;
    }
};
