#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

/*
 * 这个题的思路是简单的，就像卷积运算一样，遍历两个串的所有
 * 对齐位置，判断在每个对齐位置是否可以贴合，并且记录最长的
 * 贴合长度 maxcnt。遍历结束后， m + n - maxcnt 就是要求
 * 的结果。
 *
 * 有一些细节问题需要注意。我的对齐位置的枚举是分为两个循环
 * 完成的，即 pos < m 和 pos >= m。在前一种情况中，是自后
 * 向前逐个字符进行判断，而在后一种情况中，是自前向后的判断。
 * 此外，还要求第一个串总是比第二个串长。
 */

int main(){
    /*
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);*/
	string one, two;
	int currcnt, maxcnt, pos;
	int ix, jx;
	while(cin >> one >> two){
		if(one.size() < two.size()) swap(one, two);
		maxcnt = pos = 0;
		for(; pos < one.size(); ++pos){
			ix = pos, jx = two.size() - 1;
			currcnt = 0;
			while(ix >= 0 && jx >= 0){
				if(one[ix] - '0' + two[jx] - '0' > 3)
					break;
				++currcnt;
				--ix, --jx;
			}
			if(ix >= 0 && jx >= 0) continue;
			if(currcnt > maxcnt) maxcnt = currcnt;
		}
		for(; pos < one.size() + two.size() - 1; ++pos){
			ix = pos - two.size() + 1, jx = 0;
			currcnt = 0;
			while(ix < one.size() && jx < two.size()){
				if(one[ix] - '0' + two[jx] - '0' > 3)
					break;
				++currcnt;
				++ix, ++jx;
			}
			if(ix < one.size() && jx < two.size()) continue;
			if(currcnt > maxcnt) maxcnt = currcnt;
		}
		cout << one.size() + two.size() - maxcnt << endl;
	}
	return 0;
}
