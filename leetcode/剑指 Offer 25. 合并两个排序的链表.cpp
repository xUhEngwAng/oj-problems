class Solution {
public:
    int search(vector<int>& arr, int target) {
        int begin = 0, end = arr.size(), mid;

        while(begin < end){
            if(target == arr[begin]) return begin;
            mid = (begin + end) >> 1;
            if(arr[mid] == arr[begin]) { ++begin; continue; }
            if(arr[begin] < target && arr[mid] < arr[begin]) { end = mid; continue; }
            if(target < arr[begin] && arr[begin] < arr[mid]) { begin = mid + 1; continue; }

            if(target <= arr[mid]) end = mid;
            else begin = mid + 1;
        }

        if(begin < arr.size() && target == arr[begin]) return begin;
        return -1;
    }
};
