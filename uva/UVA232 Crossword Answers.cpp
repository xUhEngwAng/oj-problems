#include <string>
#include <vector>
#include <iostream>
#include <cstdio>
using namespace std;

/*
 * 这个题我稍微学习了紫书上面说的『自顶向下编程』，先写出了
 * 整体框架，然后再逐步实现其中调用的函数，感觉思路清晰了
 * 不少，代码结构也非常规整，也方便 debug。
 */

vector<string> board;
int r, c;

bool iscross(int row, int col){
	return col == 0 || board[row][col - 1] == '*';
}

bool isdown(int row, int col){
	return row == 0 || board[row - 1][col] == '*';
}

bool isvalid(int row, int col){
	return iscross(row, col) || isdown(row, col);
}

void print(int row, int col, int count, int down){
	printf("% 3d.", count);
	if(!down){
		while(col < c && board[row][col] != '*'){
			putchar(board[row][col]);
			++col;
		}
	}
	else{
		while(row < r && board[row][col] != '*'){
			putchar(board[row][col]);
			++row;
		}
	}
	printf("\n");
}

int main(){
	int count, rnd = 0;
	string currline;
	while(true){
		cin >> r;
		if(r == 0) break;
		cin >> c;
		board.resize(r);
		if(rnd) printf("\n");
		printf("puzzle #%d:\n", ++rnd);
		for(int ix = 0; ix != r; ++ix){
			cin >> currline;
			board[ix].assign(currline.begin(), currline.end());
		}
		printf("Across\n");
		count = 0;
		for(int ix = 0; ix != r; ++ix)
			for(int jx = 0; jx != c; ++jx){
                if(board[ix][jx] == '*') continue;
				if(isvalid(ix, jx)) ++count;
				if(iscross(ix, jx)) print(ix, jx, count, 0);
			}
		printf("Down\n");
		count = 0;
		for(int ix = 0; ix != r; ++ix)
			for(int jx = 0; jx != c; ++jx){
                if(board[ix][jx] == '*') continue;
				if(isvalid(ix, jx)) ++count;
				if(isdown(ix, jx)) print(ix, jx, count, 1);
			}
	}
	return 0;
}
