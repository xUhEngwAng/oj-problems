class Solution {
public:
    void insertQueue(const vector<int>& nums, deque<int>& q, int pos){
        while(!q.empty() && nums[q.back()] < nums[pos]) q.pop_back();
        q.push_back(pos);
    }

    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> q;
        vector<int> ret;
        int max_index;
        
        for(int ix = 0; ix != k; ++ix){
            insertQueue(nums, q, ix);
        }
        
        ret.push_back(nums[q.front()]);
        
        for(int ix = k; ix != nums.size(); ++ix){
            if(q.front() == ix-k) q.pop_front();
            insertQueue(nums, q, ix);
            ret.push_back(nums[q.front()]);
        }

        return ret;
    }
};
