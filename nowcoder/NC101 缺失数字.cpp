class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 找缺失数字
     * @param a int整型vector 给定的数字串
     * @return int整型
     */
    void swap(int &one, int &two){
        int temp = one;
        one = two;
        two = temp;
    }
    
    int partition(vector<int>& vec, int begin, int end){
        int mid = (begin + end) >> 1;
        int pivot = vec.at(mid);
        swap(pivot, vec.at(begin));
        
        int head = begin, tail = end;
        while(head < tail){
            while(tail > head && pivot < vec.at(tail)) tail--;
            if(tail > head){
                vec.at(head) = vec.at(tail);
                head += 1;
            }
            
            while(head < tail && vec.at(head) < pivot) head++;
            if(head < tail){
                vec.at(tail) = vec.at(head);
                tail -= 1;
            }
        }
        
        vec.at(head) = pivot;
        return head;
    }
    
    int solve(vector<int>& a) {
        // write code here
        int pos, begin = 0, end = a.size() - 1;
        while(begin < end){
            pos = partition(a, begin, end);
            if(a.at(pos) == pos) begin = pos + 1;
            else end = pos;
        }
        if(a.at(begin) == begin) return a.size();
        return begin;
    }
};
