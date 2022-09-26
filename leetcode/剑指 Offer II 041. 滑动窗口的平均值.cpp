#include <deque>
using namespace std;

class MovingAverage {
public:
    deque<int> window;
    int sum, _size;

    /** Initialize your data structure here. */
    MovingAverage(int size) {
        sum = 0;
        _size = size;
    }
    
    double next(int val){
        sum += val;
        window.push_back(val);
        if(_size < window.size()){
            int front = window[0];
            window.pop_front();
            sum -= front;
        }

        return (double)sum / window.size();
    }
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */
