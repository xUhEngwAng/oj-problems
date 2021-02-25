#include <list>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    list<pair<int, int>> cache;
    unordered_map<int, list<pair<int, int>>::iterator> hash;
    
    void set(int key, int value, int k){
        if(hash.find(key) != hash.end()){
            cache.erase(hash[key]);
        }
        cache.push_front({key, value});
        hash[key] = cache.begin();
        
        if(cache.size() > k){
            key = cache.back().first;  
            cache.pop_back();
            hash.erase(key);
        }
    }
    
    int get(int key){
        if(hash.find(key) == hash.end())
            return -1;
        int ret = hash[key]->second;
        cache.erase(hash[key]);
        cache.push_front({key, ret});
        hash[key] = cache.begin();
        return ret;
    }
    
    /**
     * lru design
     * @param operators int整型vector<vector<>> the ops
     * @param k int整型 the k
     * @return int整型vector
     */
    vector<int> LRU(vector<vector<int>>& operators, int k) {
        // write code here
        vector<int> ret;
        
        for(auto oper: operators){
            if(oper.front() == 1) set(oper[1], oper[2], k);
            else ret.push_back(get(oper[1]));
        }
        
        return ret;
    }
};