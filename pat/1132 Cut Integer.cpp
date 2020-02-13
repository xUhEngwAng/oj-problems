#include <string>
#include <iostream>
using namespace std;

int main(){
	int N;
    cin >> N;
	string str, one, two;
	int origin, a, b;
	for(int ix = 0; ix != N; ++ix){
		cin >> str;
		one = str.substr(0, str.size() / 2);
		two = str.substr(str.size() / 2);
		origin = stoi(str);
		a = stoi(one);
		b = stoi(two);
		if(a != 0 && b != 0 && origin % (a * b) == 0) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
