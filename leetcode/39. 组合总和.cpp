#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> res;
    vector<int> tmp;

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        for(int pos = 0; pos != candidates.size(); ++pos)
            dfs(candidates, pos, 0, target);
        return res;
    }

    void dfs(vector<int>& candidates, int pos, int curr, int target){
        int cnt = 0;
        while(curr+candidates[pos] <= target){
            curr += candidates[pos];
            tmp.push_back(candidates[pos]);
            ++cnt;
        }

        if(cnt && curr == target) res.push_back(tmp);

        while(cnt--){
            for(int ix = pos+1; ix < candidates.size(); ++ix)
                dfs(candidates, ix, curr, target);
            curr -= candidates[pos];
            tmp.pop_back();
        }
    }
};

int main(){
    int n, target;
    cin >> n >> target;
    vector<int> candidates(n);
    for(int ix = 0; ix != n; ++ix)
        cin >> candidates[ix];

    Solution solution;
    vector<vector<int>> res = solution.combinationSum(candidates, target);
    return 0;
}
