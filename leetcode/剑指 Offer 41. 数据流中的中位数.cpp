/*
 * 这个题我自己的思路只想到用一个二叉搜索树来存储这些数字，每次插入
 * 和查询中位数的时间复杂度都是 O(logn)。维护两个优先队列这个思路我
 * 感觉还是比较困难的......这里还有个细节就是第二个队列要是个小顶堆，
 * 所以每次操作都需要带上比较函数 greater<int> 这个参数。
 */

class MedianFinder {
public:
    vector<int> left, right;
    const int INF = 0x7fffffff;

    /** initialize your data structure here. */
    MedianFinder() {}
    
    void addNum(int num) {
        int lhm = left.empty()? INF: left.front();
        int rhm = right.empty()? INF: right.front(); 
        if(left.size() == right.size()){
            if(num <= rhm){
                left.push_back(num);
                push_heap(left.begin(), left.end());
            }else{
                left.push_back(right.front());
                push_heap(left.begin(), left.end());
                pop_heap(right.begin(), right.end(), greater<int>());
                right.pop_back();
                right.push_back(num);
                push_heap(right.begin(), right.end(), greater<int>());
            }
        }else{
            if(num < lhm){
                right.push_back(left.front());
                push_heap(right.begin(), right.end(), greater<int>());
                pop_heap(left.begin(), left.end());
                left.pop_back();
                left.push_back(num);
                push_heap(left.begin(), left.end());
            }else{
                right.push_back(num);
                push_heap(right.begin(), right.end(), greater<int>());
            }
        }
    }
    
    double findMedian() {
        if(left.size() == right.size())
            return (double)(left.front() + right.front()) / 2;
        else
            return left.front();
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
