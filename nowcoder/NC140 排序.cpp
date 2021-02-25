#include <vector>
using std::vector;

class Solution {
public:
    void InsertSort(vector<int>& arr, int start, int end){
        // sort arr[start, end)
        int curr, ix, jx;

        for(ix = start + 1; ix < end; ++ix){
            curr = arr[ix];

            for(jx = ix - 1; jx >= 0 && curr < arr[jx]; --jx)
                arr[jx + 1] = arr[jx];
            
            arr[jx + 1] = curr;
        }
    }

    int partition(vector<int>& arr, int start, int end){
        // partition arr[start, end) into two parts

        int pivot = arr.at(start), pos = start;
        int head = start, tail = end;

        while(true){
            while(--tail > pos && pivot < arr[tail]);
            if(tail == pos) break;
            arr[pos] = arr[tail];
            pos = tail;

            while(++head < pos && arr[head] < pivot);
            if(head == pos) break;
            arr[pos] = arr[head];
            pos = head;
        }

        arr[pos] = pivot;
        return pos;
    }

    void QuickSort(vector<int>& arr, int start, int end){
        if(end - start <= 50) InsertSort(arr, start, end);
        else{
            int pos = partition(arr, start, end);
            QuickSort(arr, start, pos);
            QuickSort(arr, pos + 1, end);
        }
    }

    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 将给定数组排序
     * @param arr int整型vector 待排序的数组
     * @return int整型vector
     */
    vector<int> MySort(vector<int>& arr) {
        // write code here
        QuickSort(arr, 0, arr.size());
        return arr;
    }
};