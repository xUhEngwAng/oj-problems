#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

/*
 * 第一次我是用了 unordered_map of unordered_set，也只是保存了所有
 * 不同的用户访问记录，然而时间和空间消耗就很大。把两个容器拆开资源
 * 消耗就好多了。理论上保存的数据是一样多的，拆开后全部数据保存在一
 * 起，还更容易出现冲突，按理说时间应该更慢才是。可能容器套容器性能
 * 就是不行吧，蛮怪的。
 */

class Solution {
public:
    vector<int> findingUsersActiveMinutes(vector<vector<int>>& logs, int k) {
        unordered_map<int, int> user_active_minutes;
        set<pair<int, int>> user_minutes;

        for(auto log : logs){
            auto um = pair<int, int>(log[0], log[1]);
            if(user_minutes.find(um) != user_minutes.end())
                continue;
            user_minutes.insert(um);
            user_active_minutes[log[0]]++;
        }

        vector<int> ret(k);
        for(auto e : user_active_minutes)
            ret[e.second-1]++;

        return ret;
    }
};
