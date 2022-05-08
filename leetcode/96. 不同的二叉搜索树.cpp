#include<vector>
using std::vector;

class Solution {
public:
    int numTrees(int n) {
        vector<int> arr(n+1, 0);
        arr[0] = 1, arr[1] = 1;

        for(int ix = 2; ix <= n; ++ix){
            for(int jx = 0; jx < ix; ++jx){
                int left = jx, right = ix - jx - 1;
                arr[ix] += arr[left] * arr[right];
            }
        }

        return arr[n];
    }
};
