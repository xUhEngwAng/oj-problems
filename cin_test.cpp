#include <iostream>
#include <string>
using namespace std;

int main(){
    string op1, op2;
    int src, dest;
    while(cin >> op1 >> src >> op2 >> dest){
        cout << op1 << ' ' << src << ' ' << op2 << ' ' << dest << endl;
    }
    return 0;
}
