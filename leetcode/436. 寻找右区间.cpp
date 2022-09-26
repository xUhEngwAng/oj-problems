#include <algorithm>
#include <vector>
#define INF (0x7fffffff)
using namespace std;

/*
 * 这个题的右区间居然可以是自己...
 */

class Solution {
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        vector<pair<int, int>> start2idx;
        start2idx.reserve(intervals.size() + 1);
        for(int ix = 0; ix != intervals.size(); ++ix){
            start2idx.emplace_back(intervals[ix][0], ix);
        }
        start2idx.emplace_back(INF, -1);
        sort(start2idx.begin(), start2idx.end(), cmp);

        vector<int> ret;
        ret.reserve(intervals.size());
        for(auto e: intervals){
            int res = getRightInterval(start2idx, e[1]);
            if(e[0] == e[1]) res += 1;
            ret.push_back(start2idx[res].second);
        }
        return ret;
    }

    int getRightInterval(const vector<pair<int, int>>& start2idx, int target){
        int head = 0, tail = start2idx.size(), mid;
        while(head < tail){
            mid = (head + tail) >> 1;
            if(target <= start2idx[mid].first) tail = mid;
            else head = mid + 1;
        }
        return head;
    }

    static bool cmp(const pair<int, int>& lh, const pair<int, int>& rh){
        return lh.first < rh.first;
    }
};
