#include <string>
#include <bitset>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int hashcode(char ch){
	if(isdigit(ch))
		return ch - '0';
	else
	if(isalpha(ch))
		return ch - 'a' + 10;
	else
		return 36;
}

int main(){
	int k, hash;
	string input;
	cin >> k >> input;
	bitset<37> stucked;
	stucked.flip();
	vector<char> res;

	for(int ix = 0, jx; ix <= input.size() - k; ++ix){
		hash = hashcode(input[ix]);
		if(!stucked[hash]) continue;
		for(jx = ix + 1; jx < ix + k; ++jx)
			if(input[jx] != input[ix]) break;
		if(jx != ix + k)
			stucked[hash] = false;
		else
        if(find(res.begin(), res.end(), input[ix]) == res.end())
            res.push_back(input[ix]);
		ix = jx - 1;
	}

	string output;
	for(int ix = 0; ix < input.size();){
		output.push_back(input[ix]);
		hash = hashcode(input[ix]);
		if(stucked[hash])
			ix += k;
		else ++ix;
	}
	for(char ch : res){
		hash = hashcode(ch);
		if(stucked[hash]) cout << ch;
	}
	cout << endl;
	cout << output << endl;
	return 0;
}
