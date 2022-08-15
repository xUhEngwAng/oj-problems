/*
 * 这个题确实很难啊。主要的难点还是在于当 arr[mid] == arr[begin]
 * 时，如何确定 mid 是处于 arr 的前半段还是后半段。实际上，从循环
 * 不变式的角度来考虑，此时可以直接忽略 arr[begin]，而并不会错过
 * 正确答案，因此直接令 begin++ 即可，即代码第 16 行。当然，此题
 * 还有不少其它细节，但类似 33 题，这里就不再赘述了。
 */

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
