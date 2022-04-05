#include <iostream>
#include <vector>

using std::vector;

class Solution{
public:
    int findKthLargest(vector<int>& nums, int k){
        int begin = 0, end = nums.size(), pos;

        while(true){
            pos = partition(nums, begin, end);
            if(pos + 1 < k) begin = pos + 1;
            else if(k < pos + 1) end = pos;
            else break;
        }

        return nums[pos];
    }

    int partition(vector<int>& nums, int begin, int end){
        int pos = begin, head = begin, tail = end, pivot = nums[head];

        while(true){
            while(pos < --tail && nums[tail] < pivot);
            if(tail == pos) break;
            nums[pos] = nums[tail];
            pos = tail;

            while(++head < pos && pivot < nums[head]);
            if(head == pos) break;
            nums[pos] = nums[head];
            pos = head;
        }
        nums[pos] = pivot;

        return pos;
    }
};

int main(){
    int n, k;
    vector<int> nums;
    scanf("%d", &n);
    nums.resize(n);
    for(int ix = 0; ix != n; ++ix)
        scanf("%d", &nums[ix]);
    scanf("%d", &k);

    Solution solution;
    int res = solution.findKthLargest(nums, k);
    printf("The Kth largest number is %d.\n", res);
    return 0;
}

