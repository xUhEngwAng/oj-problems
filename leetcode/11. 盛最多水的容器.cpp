#include <vector>
#define MIN(X, Y) ((X)<(Y)?(X):(Y))
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int begin = 0, end = height.size() - 1;
        int curr, ret = 0;

        while(begin < end){
            curr = MIN(height[begin], height[end]) * (end - begin);
            if(ret < curr) ret = curr;
            if(height[begin] < height[end]) ++begin;
            else --end;
        }

        return ret;
    }
};
