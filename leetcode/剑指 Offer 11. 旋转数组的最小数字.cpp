class Solution {
public:
    int minArray(vector<int>& numbers) {
        int begin = 0, end = numbers.size() - 1, mid;

        while(begin < end){
            mid = (begin + end) >> 1;
            if(numbers[mid] < numbers[end]) end = mid;
            else if(numbers[end] < numbers[mid]) begin = mid + 1;
            else end -= 1;
        }

        return numbers[begin];
    }
};
