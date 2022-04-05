#include <iostream>
#include <vector>

using std::vector;


class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
       quickSort(nums, 0, nums.size());
       return nums;
    }

    void quickSort(vector<int>& nums, int begin, int end){
        if(end - begin < 2) return;

        int pos = partition(nums, begin, end);
        quickSort(nums, begin, pos);
        quickSort(nums, pos+1, end);
    }

    void swap(vector<int> &nums, int src, int target){
        int tmp = nums[src];
        nums[src] = nums[target];
        nums[target] = tmp;
    }

    int partition(vector<int>& nums, int begin, int end){
        int mid = (begin + end) >> 1;
        swap(nums, begin, mid);
        int pos = begin, head = begin, tail = end, pivot = nums[head];

        while(true){
            while(pos < --tail && pivot < nums[tail]);
            if(tail == pos) break;
            nums[pos] = nums[tail];
            pos = tail;

            while(++head < pos && nums[head] < pivot);
            if(head == pos) break;
            nums[pos] = nums[head];
            pos = head;
        }

        nums[pos] = pivot;
        return pos;
    }
};
