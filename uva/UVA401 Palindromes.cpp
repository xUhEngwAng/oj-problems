#include <string>
#include <iostream>
using namespace std;

string origin = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456789";
string mirr   = "A---3--HIL-JM-O---2TUVWXY51SE-Z--8-";

int main(){
	string input, rever, mirror;
	bool isPalin, isMirror;
	int map[128];
	for(int ix = 0; ix != 35; ++ix)
		map[origin[ix]] = mirr[ix];
	while(cin >> input){
		isMirror = true;
		isPalin  = true;
		rever.assign(input.rbegin(), input.rend());
		if(rever != input)
			isPalin = false;
		mirror.clear();
		for(int ix = input.size() - 1; ix >= 0; --ix){
			if(map[input[ix]] == '-'){
				isMirror = false;
				break;
			}
			mirror.push_back(map[input[ix]]);
		}
		if(isMirror && input != mirror)
			isMirror = false;
		if(!isPalin && !isMirror)
			cout << input << " -- is not a palindrome." << endl;
		if(isPalin && !isMirror)
			cout << input << " -- is a regular palindrome." << endl;
		if(!isPalin && isMirror)
			cout << input << " -- is a mirrored string." << endl;
		if(isPalin && isMirror)
			cout << input << " -- is a mirrored palindrome." << endl;
		cout << endl;
	}
	return 0;
}
