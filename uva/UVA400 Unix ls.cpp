#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

/*
 * 这个题用到了 cout 的格式控制，主要是 setw 和 cout.setf 两个函数。
 * 两个函数都在头文件 iomanip 当中。
 * 1. setw 设置输出的长度
 * 2. cout.setf 设置对齐方式，本题目要求左对齐，所以调用了
 *    cout.setf(ios::left);
 */

string dashes = {"------------------------------------------------------------"};

int main(){
	int N, maxlen, C, currlen, R;
	string fileNames[100];
	while(cin >> N){
        maxlen = 0;
		for(int ix = 0; ix != N; ++ix){
			cin >> fileNames[ix];
			currlen = fileNames[ix].length();
			if(currlen > maxlen) maxlen = currlen;
		}
		C = 62 / (maxlen + 2);
		R = (N + C - 1) / C;
		sort(fileNames, fileNames + N);
        cout.setf(ios::left);
		cout << dashes << endl;
		for(int ix = 0; ix < R; ++ix){
			for(int jx = ix; jx < N; jx += R)
				cout << setw(maxlen + 2) << fileNames[jx];
            cout << endl;
		}
	}
	return 0;
}
