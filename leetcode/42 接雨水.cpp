#define MIN(X, Y) ((X) < (Y)? (X): (Y))

class Solution {
public:
    int area(vector<int>& height, int begin, int end){
        int ret = MIN(height[begin], height[end]) * (end - begin - 1);

        for(int ix = begin + 1; ix != end; ++ix){
            ret -= height[ix];
        }

        return ret;
    }

    int trap(vector<int>& height) {
        if(height.empty()) return 0;
        
        vector<int> next(height.size(), 0);
        vector<int> s;
        
        for(int ix = 0; ix != height.size(); ++ix){

            while(!s.empty() && height[s.back()] <= height[ix]){
                next[s.back()] = ix;
                s.pop_back();
            }

            s.push_back(ix);
        }

        for(int ix = 0; ix < s.size() - 1; ++ix){
            next[s.at(ix)] = s.at(ix + 1);
        }

        int ret = 0, curr = 0;

        while(curr < height.size() - 1){
            ret += area(height, curr, next[curr]);
            curr = next[curr];
        }

        return ret;
    }
};