#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>
using namespace std;
bool isPrime(int value){
	if (value == 2) return 1;
	int endloop = sqrt(value) + 1;
	for(int ix = 2; ix < endloop; ix++){
		if (value % ix == 0) return 0;
	}
	return 1;
}
int main(){
	int L, K, subvalue;
	scanf("%d %d", &L, &K);
	string srcDigits;
	cin >> srcDigits;
	for(int begin = 0; begin != L - K + 1; begin++){
		subvalue = stoi(srcDigits.substr(begin, K));
		if(isPrime(subvalue)){
			cout << srcDigits.substr(begin, K) << endl;
			system("pause");
			return 0;
		}
	}
	printf("404\n");
	system("pause");
	return 0;
}
