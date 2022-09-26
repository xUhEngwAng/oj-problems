class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        if(k == 0 || arr.size() == 0) return vector<int>();
        vector<int> ret(arr.begin(), arr.begin() + k);
        make_heap(ret.begin(), ret.end(), less<int>());
        
        for(int ix = k; ix != arr.size(); ++ix){
            if(arr[ix] < ret.front()){
                pop_heap(ret.begin(), ret.end());
                ret.pop_back();
                ret.push_back(arr[ix]);
                push_heap(ret.begin(), ret.end());
            }
        }

        return ret;
    }
};
