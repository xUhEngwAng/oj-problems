#include <string>
#include <iostream>
using namespace std;

int main(){
	string s, t;
	int pos;
	while(cin >> s >> t){
		pos = 0;
		for(int ix = 0; ix != t.size(); ++ix){
			if(t[ix] == s[pos])
				++pos;
			if(pos == s.size()) break;
		}
		if(pos == s.size()) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
	return 0;
}
