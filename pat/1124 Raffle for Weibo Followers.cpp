#include <string>
#include <iostream>
#include <set>
using namespace std;

int main(){
	int M, N, S;
	cin >> M >> N >> S;
	set<string> winner;
	string str;

	if(S > M){
		while(M--) cin >> str;
		cout << "Keep going..." << endl;
		return 0;
	}

	for(int ix = 0; ix != S; ++ix){
		cin >> str;
	}
	winner.insert(str);
	cout << str << endl;
	int count = 0;
	for(int ix = 0; ix != M - S; ++ix){
		cin >> str;
		if(++count == N){
			if(winner.find(str) != winner.end())
				--count;
			else{
				count = 0;
				winner.insert(str);
				cout << str << endl;
			}
		}
	}
	return 0;
}
