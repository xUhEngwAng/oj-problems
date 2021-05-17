#include <iostream>
#include <string>

void remove_once(std::string &n){
    int len = n.length();
    int ix;
    for(ix = 0; ix < len - 1; ++ix){
        if(n[ix] < n[ix+1]){
            n.erase(ix, 1);
            return;
        }
    }
    n.pop_back();
}

int main(){
    int T, k;
    std::string n;
    std::cin >> T;
    for(int ix = 0; ix != T; ++ix){
        std::cin >> n >> k;
        while(k--) remove_once(n);
        std::cout << n << std::endl;
    }
    return 0;
}

