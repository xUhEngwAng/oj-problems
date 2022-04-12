#include <unordered_map>

struct LRUNode {
    int key, val;
    LRUNode* next;

    LRUNode(): key(-1), next(nullptr) {}
    LRUNode(int k): key(k), next(nullptr) {}
    LRUNode(int k, int v): key(k), val(v), next(nullptr) {}
};

class LRUCache {
public:
    std::unordered_map<int, LRUNode*> hashtable;
    LRUNode *head, *tail;
    int max_capacity;

    LRUCache(int capacity) {
        head = new LRUNode();
        tail = head;
        max_capacity = capacity;
    }
    
    int get(int key) {
        if(hashtable.find(key) == hashtable.end()) return -1;
        
        LRUNode *prev = hashtable[key], *curr = prev->next;
        if(curr != tail){
            prev->next = curr->next;
            hashtable[prev->next->key] = prev;
            tail->next = curr;
            curr->next = nullptr;
            hashtable[key] = tail;
            tail = curr;
        }
        return curr->val;
    }
    
    void put(int key, int value) {
        int val = get(key);
        if(val != -1){
            tail->val = value;
            return;
        }
        if(hashtable.size() == max_capacity)
            removeLRU();
        LRUNode* curr = new LRUNode(key, value);
        tail->next = curr;
        hashtable[key] = tail;
        tail = curr;
    }

    void print(){
        LRUNode *n = head;
        printf("(%d, %d)", n->key, n->val);
        n = n->next;

        while(n){
            printf("->(%d, %d)", n->key, n->val);  
            n = n->next;
        }

        printf(" tail: (%d, %d)\n", tail->key, tail->val);
    }

    void removeLRU(){
        LRUNode *lru = head->next;
        head->next = lru->next;
        if(head->next) hashtable[head->next->key] = head;
        else tail = head;
        hashtable.erase(lru->key);
    }
};

int main(){
    LRUCache cache(2);
    int val;
    cache.print();
    cache.put(1, 1);
    cache.print();
    cache.put(2, 2);
    cache.print();
    val = cache.get(1);
    cache.print();
    printf("The value of key %d is %d.\n", 1, val);
    cache.put(3, 3);
    cache.print();
    val = cache.get(2);
    printf("The value of key %d is %d.\n", 2, val);
    cache.put(4, 4);
    cache.print();
    val = cache.get(4);
    cache.print();
    
    val = cache.get(1);
    printf("The value of key %d is %d.\n", 1, val);
    cache.print();
    val = cache.get(3);
    printf("The value of key %d is %d.\n", 3, val);
    cache.print();
    val = cache.get(4);
    printf("The value of key %d is %d.\n", 4, val);
    cache.print();
    return 0;
}

