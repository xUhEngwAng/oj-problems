#include <string>
#include <vector>
#include <iostream>
#include <map>
using namespace std;

vector<string> units = {"tret", "jan", "feb", "mar", "apr", "may",
                         "jun", "jly", "aug", "sep", "oct", "nov", "dec"};
vector<string> tens = {"tret", "tam", "hel", "maa", "huh", "tou", "kes",
                       "hei", "elo", "syy", "lok", "mer", "jou"};

int main(){
	map<string, int> m;
	for(int ix = 0; ix != 13; ++ix)
		m[units[ix]] = ix;
	for(int ix = 1; ix != 13; ++ix)
		m[tens[ix]] = 13 * ix;

	int N;
	cin >> N;
	cin.ignore();
	string oneline, one, two, resStr;
	int num, res, pos;
	while(N--){
		one.clear(), two.clear();
		res = 0, resStr.clear();
		getline(cin, oneline);
		if(isdigit(oneline[0])){
			num = stoi(oneline);
			one = units[num % 13];
			num /= 13;
			if(num != 0) two = tens[num];
			if(!two.empty()) resStr += two;
			if(resStr.empty() || one != "tret"){
                if(!resStr.empty()) resStr.push_back(' ');
                resStr += one;
			}
			cout << resStr << endl;
		}else{
			pos = oneline.find(' ');
			if(pos == -1){
				one = oneline;
				two = "tret";
			}
			else{
				one = oneline.substr(0, pos);
				two = oneline.substr(pos + 1);
			}
			res += m[one] + m[two];
			cout << res << endl;
		}
	}
	return 0;
}
