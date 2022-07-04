class Solution {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        int min_abs = 0x7fffffff, curr_abs;
        vector<vector<int>> ret;
        sort(arr.begin(), arr.end());

        for(int ix = 0; ix != arr.size() - 1; ++ix){
            curr_abs = arr[ix+1] - arr[ix];
            if(curr_abs < min_abs){
                min_abs = curr_abs;
                ret.clear();
                ret.push_back({arr[ix], arr[ix+1]});
            }else
            if(curr_abs == min_abs)
                ret.push_back({arr[ix], arr[ix+1]});
        }

        return ret;
    }
};
