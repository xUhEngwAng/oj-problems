#include <iostream>
#include <string>
#include <map>
using namespace std;

const string alphanum = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

void lower(string& str){
	for(auto it = str.begin(); it != str.end(); ++it)
		if(*it >= 'A' && *it <= 'Z')
            *it = *it - 'A' + 'a';
}

int main(){
	string origin, curr;
	getline(cin, origin);
	map<string, int> m;
	int end = 0, pos = 0, len = origin.size();
	while(true){
		pos = origin.find_first_of(alphanum, end);
		if(pos == -1) break;
		end = origin.find_first_not_of(alphanum, pos);
		if(end == -1) end = len;
		curr = origin.substr(pos, end - pos);
		lower(curr);
		if(m.find(curr) != m.end()) m[curr]++;
		else m[curr] = 1;
	}
	int maxCount = 0;
	string maxStr;
	for(auto e : m){
		if(e.second > maxCount){
			maxCount = e.second;
			maxStr = e.first;
		}
	}
	cout << maxStr << " " << maxCount << endl;
	return 0;
}
