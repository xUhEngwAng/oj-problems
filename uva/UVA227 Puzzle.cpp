#include <string>
#include <vector>
#include <iostream>
using namespace std;

/*
 * 这个题还是挺繁琐的，逻辑是比较简单，但是需要注意不少
 * 细节问题。其中主要的是输出格式的问题，题目上是说不同
 * 谜题的输出之间应该空一行，所以显然最后一个输出后面就
 * 不能也多空一行了，注意到这个问题我就通过了。
 */

int main(){
	vector<vector<char>> board(5, vector<char>(5));
	int xpos, ypos, count = 0;
	bool flag;
	string currline, moves;
	while(true){
		for(int jx = 0; jx != 5; ++jx){
			getline(cin, currline);
			if(currline == "Z") break;
			for(int ix = 0; ix != 5; ++ix){
				if(currline[ix] == ' '){
					xpos = jx;
					ypos = ix;
				}
				board[jx][ix] = currline[ix];
			}
		}
		if(currline == "Z") break;
		if(count) cout << endl;
		cout << "Puzzle #" << ++count << ":" << endl;
		moves.clear();
		while(true){
			cin >> currline;
			moves += currline;
			if(currline.back() == '0') break;
		}
		flag = true;
		for(char ch : moves){
			switch(ch){
				case 'A':
					if(xpos == 0) flag = false;
					else{
						board[xpos][ypos] = board[xpos - 1][ypos];
						board[xpos - 1][ypos] = ' ';
						xpos -= 1;
					}
				break;
				case 'B':
					if(xpos == 4) flag = false;
					else{
						board[xpos][ypos] = board[xpos + 1][ypos];
						board[xpos + 1][ypos] = ' ';
						xpos += 1;
					}
				break;
				case 'R':
					if(ypos == 4) flag = false;
					else{
						board[xpos][ypos] = board[xpos][ypos + 1];
						board[xpos][ypos + 1] = ' ';
						ypos += 1;
					}
				break;
				case 'L':
					if(ypos == 0) flag = false;
					else{
						board[xpos][ypos] = board[xpos][ypos - 1];
						board[xpos][ypos - 1] = ' ';
						ypos -= 1;
					}
				break;
				default:;
			}
			if(!flag) break;
		}
		if(flag){
			for(int jx = 0; jx != 5; ++jx)
				cout << board[jx][0] << ' ' << board[jx][1] << ' ' << board[jx][2] << ' '
			         << board[jx][3] << ' ' << board[jx][4] << endl;
		}
		else
			cout << "This puzzle has no final configuration." << endl;
        cin.ignore();
	}
	return 0;
}
