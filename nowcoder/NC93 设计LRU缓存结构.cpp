#include <vector>
#include <unordered_map>
using std::vector;
using std::unordered_map;

struct node{
    int value;
    int time;
    node() = default;
    node(int v, int t): value(v), time(t) {}
};

class Solution {
public:
    /**
     * lru design
     * @param operators int整型vector<vector<>> the ops
     * @param k int整型 the k
     * @return int整型vector
     */
    vector<int> LRU(vector<vector<int>>& operators, int k) {
        // write code here
        unordered_map<int, node> cache;
        unordered_map<int, node>::iterator pos;
        vector<int> ret;
        int key, value, op, min;

        for(int ix = 0; ix != operators.size(); ++ix){
            auto oper = operators[ix];

            if(oper.front() == 1){ // set(x, y)
                key = oper.at(1), value = oper.at(2);
                cache[key] = node(value, ix);
                if(cache.size() > k){
                    min = 0x7fffffff;

                    for(auto it = cache.begin(); it != cache.end(); ++it){
                        if(it->second.time < min) {
                            min = it->second.time;
                            pos = it;
                        }
                    }

                    cache.erase(pos->first);
                }
            }

            else
            if(oper.front() == 2){ // get(x)
                key = oper.at(1);
                if(cache.find(key) == cache.end()) value = -1;
                else{
                    cache[key].time = ix;
                    value = cache[key].value;
                }
                ret.push_back(value);
            }
            else; //handle exception
        }

        return ret;
    }
};