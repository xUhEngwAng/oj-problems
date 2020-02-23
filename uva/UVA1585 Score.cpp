#include <iostream>
#include <string>
using namespace std;

int main(){
	int N, count, score;
	string input;
	cin >> N;
	while(N--){
		score = count = 0;
		cin >> input;
		for(int ix = 0; ix != input.size(); ++ix){
			if(input[ix] == 'O') ++count;
			else count = 0;
			score += count;
		}
		cout << score << endl;
	}
	return 0;
}
