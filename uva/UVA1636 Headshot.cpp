#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main(){
	string str;
	int zero_cnt, survival;
	double p1, p2;
	while(cin >> str){
		zero_cnt = survival = 0;
		for(int ix = 0; ix != str.size() - 1; ++ix)
			if(str[ix] == '0'){
				++zero_cnt;
				if(str[ix+1] == '0') ++survival;
			}
		if(str.back() == '0'){
			++zero_cnt;
			if(str[0] == '0') ++survival;
		}
		p1 = (double)survival / zero_cnt;
		p2 = (double)zero_cnt / str.size();
		if(fabs(p1 - p2) < 1e-5) cout << "EQUAL" << endl;
		else if(p1 > p2) cout << "SHOOT" << endl;
		else cout << "ROTATE" << endl;
	}
	return 0;
}
