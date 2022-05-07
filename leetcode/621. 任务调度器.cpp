#include <iostream>
#include <map>
#include <vector>
using namespace std;

/*
 * 这个题我写的很糟糕，它告诉我开始 coding 之前还是得先
 * 做好规划。这个题每一步只需要选择冷却好了且剩余数量最
 * 多的任务，由于要选择最多，我计划是用一个堆作为底层结
 * 构。写了下才发现，堆的话我应该怎么判断一个任务有没有
 * 冷却好呢？要是增加这个信息到堆中，这个堆将需要支持上
 * 移操作，就变得非常麻烦，时间复杂度也会增加不少。
 *
 * 因此最终还是使用了两个 map 来保存剩余数量和冷却时间
 * 两个信息。每次都遍历所有的任务，来找到符合要求的任务。
 * 还有一开始的时间是单步增加的，如果 n 很大将会显著增加
 * 循环的数量。实际上只需每次将时间快进到下一个任务冷却
 * 好了即可，这样修改后运行速度快了整整一倍。
 */

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        map<char, int> task_cnt, task_avail_time;
        for(char task : tasks)
            task_cnt[task] += 1;
        for(auto e : task_cnt)
            task_avail_time[e.first] = 0;

        int nsteps = 1, max_cnt, min_avail_time;
        char task;

        while(!task_cnt.empty()){
            max_cnt = 0;
            min_avail_time = 0x7fffffff;

            for(auto e : task_avail_time){
                char curr = e.first;
                if(e.second < min_avail_time)
                    min_avail_time = e.second;
                if(e.second <= nsteps && max_cnt < task_cnt[curr]){
                    max_cnt = task_cnt[curr];
                    task = curr;
                }
            }

            if(max_cnt > 0){
                if(!--task_cnt[task]){
                    task_cnt.erase(task);
                    task_avail_time.erase(task);
                }
                else
                    task_avail_time[task] = nsteps + n + 1;
                nsteps++;
            }
            else
                nsteps = min_avail_time;
        }

        return nsteps - 1;
    }
};

int main(){
    int m, n;
    cin >> m >> n;
    vector<char> tasks(m);
    for(int ix = 0; ix != m; ++ix)
        cin >> tasks[ix];

    Solution solution;
    int ans = solution.leastInterval(tasks, n);
    cout << "The answer is " << ans << endl;
    return 0;
}

