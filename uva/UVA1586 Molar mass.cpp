#include <string>
#include <iostream>
#include <cstdio>
#include <map>
using namespace std;

map<char, double> mass;

int getCnt(const string& str, int &pos){
	int res = 1, cnt = 0;
	while((pos + cnt) < str.size() &&
		 isdigit(str[pos + cnt])) ++cnt;
	if(cnt != 0)
		res = stoi(str.substr(pos, cnt));
	pos += cnt;
	return res;
}

int main(){
	int N, cnt;
	cin >> N;
	mass['C'] = 12.01;
	mass['H'] = 1.008;
	mass['O'] = 16.00;
	mass['N'] = 14.01;
	string input;
	char curr;
	double res;
	while(N--){
		res = 0.0;
		cin >> input;
		for(int ix = 0; ix < input.size();){
			curr = input[ix++];
			cnt = getCnt(input, ix);
			res += mass[curr] * cnt;
		}
		printf("%.3f\n", res);
	}
	return 0;
}
