#include <iostream>
#include <iomanip>
#include <string>
#define MAX(X,Y) ((X)>(Y)?(X):(Y))
using namespace std;
int main(){
	string inputStr;
	cin >> inputStr;
	int n1, n2, inputlen;
	inputlen = inputStr.size();
	n2 = MAX(3, (inputlen + 2) / 3); // n1 + n2 + n3 - 2 = N
	while(1){
		if((inputlen - n2) % 2 != 0){
			n2 += 1;
			continue;
		}
		n1 = (inputlen + 2 - n2) / 2;
		if (n1 <= n2) break;
		n2 += 1;
	}
	//print
	string::iterator headIt, tailIt;
	int idx;
	for(headIt = inputStr.begin(), tailIt = inputStr.end()-1, idx = 0; idx != n1 - 1; idx++, headIt++, tailIt--){
		cout << *headIt << setw(n2-1) << *tailIt << endl;
	}
	cout << string(headIt, tailIt + 1);
	system("pause");
	return 0;
}
