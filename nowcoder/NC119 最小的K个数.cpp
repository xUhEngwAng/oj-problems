class Solution {
public:
    int partition(vector<int>& input, int begin, int end){
        int pivot = input.at(begin);
        int pos = begin, head = begin, tail = end;
        
        while(true){
            while(--tail > pos && pivot < input[tail]);
            if(tail == pos) break;
            input[pos] = input[tail];
            pos = tail;
            
            while(++head < pos && input[head] < pivot);
            if(head == pos) break;
            input[pos] = input[head];
            pos = head;
        }
        
        input[pos] = pivot;
        return pos;
    }
    
    int QuickSelect(vector<int>& input, int begin, int end, int k){
        int pos = partition(input, begin, end);
        if(pos - begin <  k - 1) 
            return QuickSelect(input, pos + 1, end, k + begin - pos - 1);
        if(pos - begin >  k - 1) 
            return QuickSelect(input, begin, pos, k);
        else 
            return input[pos];
    }
    
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        // QuickSelect solution
        vector<int> ret;
        if(k > input.size() || input.size() == 0 || k == 0) return ret;
        int kth = QuickSelect(input, 0, input.size(), k);
        
        for(int e: input)
            if(e < kth)
                ret.push_back(e);
        
        ret.push_back(kth);
        return ret;
        
        // naive solution based on heap
        /*vector<int> ret;
        if(k > input.size()) return ret;
        make_heap(input.begin(), input.end(), greater<int>());
        
        while(k--){
            pop_heap(input.begin(), input.end(), greater<int>());
            ret.push_back(input.back());
            input.pop_back();
        }
        
        return ret;*/
    }
};