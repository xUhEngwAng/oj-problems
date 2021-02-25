class Solution {
public:
    int partition(vector<int>& arr, int begin, int end){
        int pivot = arr.at(begin);
        int pos = begin, head = begin, tail = end;
        
        while(true){
            while(--tail > pos && pivot > arr[tail]);
            if(tail == pos) break;
            arr[pos] = arr[tail];
            pos = tail;
            
            while(++head < pos && arr[head] > pivot);
            if(head == pos) break;
            arr[pos] = arr[head];
            pos = head;
        }
        
        arr[pos] = pivot;
        return pos;
    }
    
    int QuickSelect(vector<int>& arr, int begin, int end, int K){
        int pos = partition(arr, begin, end);
        if(pos - begin <  K - 1)
            return QuickSelect(arr, pos + 1, end, K + begin - pos - 1);
        if(pos - begin >  K - 1)
            return QuickSelect(arr, begin, pos, K);
        
        return arr[pos];
    }
    
    int findKth(vector<int> a, int n, int K) {
        // write code here
        return QuickSelect(a, 0, n, K);
    }
};