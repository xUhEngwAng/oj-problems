#include <algorithm>
#include <vector>
#include <cstdio>
using std::sort;
using std::vector;

class Solution {
public:
    vector<bool> visited;
    vector<int> curr;
    vector<vector<int>> ret;

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        visited.resize(nums.size(), false);
        int prev = 0x7fffffff;

        for(int ix = 0; ix != nums.size(); ++ix){
            if(nums[ix] == prev) continue;
            dfs(nums, ix);
            prev = nums[ix];
        }

        return ret;
    }

    void dfs(const vector<int>& nums, int pos){
        curr.push_back(nums[pos]);
        visited[pos] = true;
        int prev = 0x7fffffff;

        for(int ix = 0; ix != nums.size(); ++ix){
            if(visited[ix]) continue;
            if(nums[ix] == prev) continue;
            dfs(nums, ix);
            prev = nums[ix];
        }
         
        if(curr.size() == nums.size()) ret.push_back(curr);
        visited[pos] = false;
        curr.pop_back();
    }
};

int main(){
    int n;
    scanf("%d", &n);
    vector<int> nums(n);
    for(int ix = 0; ix != n; ++ix)
        scanf("%d", &nums[ix]);

    Solution solution;
    vector<vector<int>> res = solution.permuteUnique(nums);
    for(auto v : res){
        printf("[ ");
        for(auto e: v){
            printf("%d ", e);        
        }
        printf("]\n");
    }

    return 0;
}
