#include <string>
#include <iostream>
using namespace std;

int main(){
	int d, N;
	int pos, ix;
	cin >> d >> N;
	string curr, next;
	curr.push_back(d + '0');
	while(--N){
		pos = 0;
		while(pos < curr.size()){
			ix = pos + 1;
			while(ix < curr.size() &&
				  curr[pos] == curr[ix]) ++ix;
			next.push_back(curr[pos]);
			next.push_back(ix - pos + '0');
			pos = ix;
		}
		curr.assign(next);
		next.clear();
	}
	cout << curr << endl;
	return 0;
}
