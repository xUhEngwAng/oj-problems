class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        if(arr.empty()) return vector<int>();
        vector<int> rank, ret(arr.size());
        rank.reserve(arr.size());
        for(int ix = 0; ix != arr.size(); ++ix){
            rank.push_back(ix);
        }
        sort(rank.begin(), rank.end(), [&](int lh, int rh){ return arr[lh] < arr[rh]; });
        ret[rank[0]] = 1;
        for(int ix = 1; ix != arr.size(); ++ix){
            if(arr[rank[ix]] == arr[rank[ix-1]]) ret[rank[ix]] = ret[rank[ix-1]];
            else ret[rank[ix]] = ret[rank[ix-1]] + 1;
        }

        return ret;
    }
};
