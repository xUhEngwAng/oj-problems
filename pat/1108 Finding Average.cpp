#include <string>
#include <iostream>
using namespace std;

int main(){
	string a = "aaa", b = "..1.2.3a", c = "9999";
	cout << stod(b) << endl;
	system("pause");
	cout << stod(b) << endl;
	system("pause");
	cout << stod(c) << endl;
	return 0;
}
