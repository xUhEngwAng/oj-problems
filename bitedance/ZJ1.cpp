#include <cstdio>
#include <vector>
#define MOD (1000000007)
using std::vector;

int main(){
    int n, curr = 1, ret = 0;
    scanf("%d", &n);
    // best solution: O(n)
    
    // solution based on dp: O(n^2) in worse case
    vector<int> pi, first, second;
    pi.resize(n + 1);
    first.resize(n + 1, 0);
    second.resize(n + 1, 1);
    
    for(int ix = 1; ix <= n; ++ix){
        scanf("%d", &pi[ix]);
    }
    
    for(int ix = 2; ix <= n; ++ix){
        first[ix] = first[ix-1] + second[ix-1] + 1;
        if(first[ix] >= MOD) first[ix] -= MOD;
        
        for(int tmp = pi[ix]; tmp != ix; ++tmp){
            second[ix] = second[ix] + second[tmp] + 1;
            if(second[ix] >= MOD) second[ix] -= MOD;
        }
    }
    
    ret = first[n] + second[n] + 1;
    if(ret >= MOD) ret -= MOD;
    printf("%d\n", ret);
    
    // brute-force solution: O(2^n) in worst case
    /*
    vector<int> next, cnt;
    next.resize(n + 1);
    cnt.resize(n + 1, 0);
    
    for(int ix = 1; ix <= n; ++ix){
        scanf("%d", &next[ix]);
    }
    
    while(curr != n + 1){
        cnt[curr] = cnt[curr] ^ 1;
        if(cnt[curr] == 1) curr = next[curr];
        else curr = curr + 1;
        if(++ret == MOD) ret -= MOD;
    }
    
    printf("%d\n", ret);
    */
    
    return 0;
}
