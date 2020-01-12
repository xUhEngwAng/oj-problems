#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string getUnit(int count);

string digits[10] = {"ling", "yi", "er", "san", "si",
                     "wu", "liu", "qi", "ba", "jiu"};
string units[4] = {"", " Shi", " Bai", " Qian"};

int main(){
	string input, res;
	cin >> input;

	int len = input.length(), count = len, ix = 0;
	bool zeroflag = false;
	if(input.front() == '-'){
        res.append("Fu ");
        ++ix, --count;
	}

	//remove prefix zero
    while(ix < len - 1 && input[ix] == '0'){++ix, --count;}

    res.append(digits[input[ix++] - '0']);
    res.append(getUnit(count--));

	for(; ix != len; ++ix, --count){
		if(input[ix] != '0'){
			if(zeroflag){
                res.append(" ling");
                zeroflag = false;
			}
			res.push_back(' ');
			res.append(digits[input[ix] - '0']);
			res.append(getUnit(count));
		}
		else{
            if(count == 5 || count == 9)
                res.append(getUnit(count));
            else zeroflag = true;
        }
	}
	cout << res << endl;
	return 0;
}

string getUnit(int count){
	if(count == 5) return " Wan";
	if(count == 9) return " Yi";

	return units[(count - 1) % 4];
}
