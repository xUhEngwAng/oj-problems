class Solution {
public:
    /**
     * return topK string
     * @param strings string字符串vector strings
     * @param k int整型 the k
     * @return string字符串vector<vector<>>
     */
    static bool cmp(const pair<string, int>& one, const pair<string, int>& two){
        if(one.second == two.second)
            return one.first > two.first;
        return one.second < two.second;
    }
    
    vector<vector<string>> topKstrings(vector<string>& strings, int k) {
        // write code here
        unordered_map<string, int> str2int;
        for(int ix = 0; ix != strings.size(); ++ix){
            str2int[strings.at(ix)] += 1;
        }
        vector<pair<string, int>> heap;
        heap.reserve(str2int.size());
        for(auto it = str2int.begin(); it != str2int.end(); ++it){
            heap.push_back({it->first, it->second});
        }
        vector<vector<string>> ret;
        string str, count;
        make_heap(heap.begin(), heap.end(), cmp);
        for(int ix = 0; ix != k; ++ix){
            str = heap.front().first;
            count = to_string(heap.front().second);
            ret.push_back(vector<string>({str, count}));
            pop_heap(heap.begin(), heap.end(), cmp);
            heap.pop_back();
        }
        return ret;
    }
};
