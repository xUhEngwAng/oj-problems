#include <string>
#include <stdio.h>
#include <iostream>
using namespace std;
int main(){
	string s1, s2;
	getline(cin, s1);
	getline(cin, s2);
	for(auto It = s1.begin(); It != s1.end(); It++){
		if (s2.find(*It) == -1) printf("%c", *It);
	}
	system("pause");
	return 0;
}
