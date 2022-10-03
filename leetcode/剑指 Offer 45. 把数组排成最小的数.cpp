#include <algorithm>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    static bool cmp(const string& lh, const string& rh){
        return lh + rh < rh + lh;
    }

    string minNumber(vector<int>& nums) {
        vector<string> nums_str;
        nums_str.reserve(nums.size());

        for(auto num : nums)
            nums_str.push_back(to_string(num));

        sort(nums_str.begin(), nums_str.end(), cmp);
        string ret;

        for(auto str : nums_str){
            ret += str;
        }

        return ret;
    }
};
