#include <iostream>
#include <string>
using namespace std;

string commonSuffix(string one, string two){
	int onelen = one.length();
	int ix = onelen - 1, jx = two.length() - 1;
	while(ix >= 0 && jx >= 0 && one[ix] == two[jx]){
		--ix, --jx;
	}
	return one.substr(ix + 1, onelen - ix - 1);
}

int main(){
	int N;
	cin >> N;
	cin.ignore();
	string curr, res;
	getline(cin, curr);
	res = curr;
	for(int ix = 1; ix != N; ++ix){
		getline(cin, curr);
		res = commonSuffix(curr, res);
	}
	if(res.empty()) cout << "nai" << endl;
	else            cout << res << endl;
	return 0;
}
