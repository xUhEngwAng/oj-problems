#include <string>
#include <iostream>
#include <set>
using namespace std;

int main(){
	int round, count;
	string solution, guess;
	set<char> s;
	while(true){
		cin >> round;
		if(round == -1) break;
		cout << "Round " << round << endl;
		cin >> solution >> guess;
		for(char ch : solution)
			s.insert(ch);
		count = 0;
		for(char ch : guess){
			if(s.find(ch) != s.end()) s.erase(ch);
			else ++count;
			if(s.empty()){
				cout << "You win." << endl;
				break;
			}
			if(count == 7){
				cout << "You lose." << endl;
				break;
			}
		}
		if(!s.empty() && count < 7)
			cout << "You chickened out." << endl;
		s.clear();
	}
	return 0;
}
