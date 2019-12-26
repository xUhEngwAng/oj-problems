#include <iostream>
#include <string>
using namespace std;
string eliminate(string str, int pos){
	int begin, end;
	begin = end = pos;
	while (true) {
		if (begin >= 1 && str[begin - 1] == str[pos]) {
			begin -= 1;
			if (begin >= 1 && str[begin - 1] == str[pos]) begin -= 1;
		}
		if (end <= str.length() - 2 && str[end + 1] == str[pos]) {
			end += 1;
			if (end <= str.length() - 2 && str[end + 1] == str[pos]) end += 1;
		}
		if (end - begin < 2) break;
		str = str.erase(begin, end - begin + 1);
		pos = begin = end = begin - 1;
	}
	return str;
}
int main(){
	string str;
	getline(cin, str);
	int n;
	cin >> n;
	int pos;
	char letter;
	for(int ix = 0; ix != n; ++ix){
		cin >> pos >> letter;
		str.insert(pos, 1, letter);
		str = eliminate(str, pos);
		if (str.empty()) cout << '-' << endl;
		else cout << str << endl;
	}

	//system("pause");
	return 0;
}
