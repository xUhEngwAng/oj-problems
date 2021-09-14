class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 计算成功举办活动需要多少名主持人
     * @param n int整型 有n个活动
     * @param startEnd int整型vector<vector<>> startEnd[i][0]用于表示第i个活动的开始时间，startEnd[i][1]表示第i个活动的结束时间
     * @return int整型
     */
    static bool cmp(const pair<int, int>& lh, const pair<int, int>& rh){
        if(lh.first != rh.first)
            return lh.first < rh.first;
        return lh.second < rh.second;
    }
    
    int minmumNumberOfHost(int n, vector<vector<int>>& startEnd) {
        // write code here
        vector<pair<int, int>> time_point;
        for(auto entry : startEnd){
            time_point.push_back({entry[0], 1});
            time_point.push_back({entry[1], 0});
        }
        sort(time_point.begin(), time_point.end(), cmp);
        int total = 0, curr = 0;
        for(auto entry : time_point){
            if(!entry.second) curr += 1;
            else{
                if(curr > 0) curr -= 1;
                else total += 1;
            }
        }
        
        return total;
    }
};
