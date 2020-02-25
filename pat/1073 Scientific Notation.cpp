#include <string>
#include <iostream>
using namespace std;

int main(){
	string input, output, signif;
	cin >> input;
	if(input.front() == '-') output.push_back('-');
	signif.push_back(input[1]);
	for(int ix = 3; input[ix] != 'E'; ++ix)
		signif.push_back(input[ix]);
	int exppos = input.find('E');
	int exp = stoi(input.substr(exppos + 1));
	/*cout << exp << endl;
	cout << signif << endl;*/
	if(exp < 0){
		cout << output << "0.";
		while(++exp != 0)
			cout << '0';
		cout << signif << endl;
	}
	else
	if(exp >= signif.size() - 1){
		cout << output << signif;
		for(int ix = 0; ix != exp - signif.size() + 1; ++ix)
			cout << '0';
		cout << endl;
	}
	else{
		cout << output << signif.substr(0, exp + 1)
		     << '.' << signif.substr(exp + 1) << endl;
	}
	return 0;
}
