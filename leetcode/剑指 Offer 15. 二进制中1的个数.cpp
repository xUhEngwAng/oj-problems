class Solution {
public:
    int hammingWeight(uint32_t n) {
        int ret = 0;

        while(n){
            if(n & 1) ret += 1;
            n = n >> 1;
        }

        return ret;
    }
};
