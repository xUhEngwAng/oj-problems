#include <iostream>
#include <string>
int main(){
	std::string str;
	std::getline(std::cin, str); //c++ use of std::getline
	int count[26] = { 0 };
	int idx;
	char ch;
	for (int ix = 0; ix != str.length(); ++ix) {
		ch = str[ix];
		if (ch >= 'a' && ch <= 'z') idx = ch - 'a';
		else if (ch >= 'A' && ch <= 'Z') idx = ch - 'A';
		else continue;
		++count[idx];
	}
	for(int ix = 0; ix != 26; ++ix){
		if (count[ix]) std::cout << char('A' + ix) << ": " << count[ix] << std::endl;
	}
	return 0;
}
