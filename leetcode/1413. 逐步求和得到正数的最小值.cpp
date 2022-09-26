#define MAX(X, Y) ((X)<(Y)?(Y):(X))

class Solution {
public:
    int minStartValue(vector<int>& nums) {
        int minsum = 0x7fffffff, curr = 0;

        for(auto num : nums){
            if((curr += num) < minsum)
                minsum = curr;
        }

        return MAX(1, 1-minsum);
    }
};
