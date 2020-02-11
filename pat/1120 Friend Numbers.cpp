#include <string>
#include <iostream>
#include <set>
using namespace std;

int main(){
	int N, friendid;
	cin >> N;
	string curr;
	set<int> res;
	for(int ix = 0; ix != N; ++ix){
		cin >> curr;
		friendid = 0;
		for(char ch : curr)
			friendid += ch - '0';
		res.insert(friendid);
	}
	cout << res.size() << endl;
	auto it = res.begin();
	cout << *it;
	for(++it; it != res.end(); ++it)
		cout << ' ' << *it;
	return 0;
}
