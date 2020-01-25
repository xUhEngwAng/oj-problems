#include <string>
#include <vector>
#include <iostream>
using namespace std;

#define CONST  (1000000007)

/*
 * 这个题做对我还破费了一番周折。看到这个题我就想『这不就是LCS的变种吗？』
 * 于是就按照 LCS 的思路想了半天，无果。最后还是跳出了 LCS 的框架，
 * 重新进行思考才得到答案。我的方法其实还是类似于 LCS 的解法，维护了一个
 * count 数组来保存当前位置以前所有匹配的数量，更新规则是
 * if p[ix - 1] == str[jx - 1]
 *     count[ix][jx] = count[ix-1][jx-1] + count[ix][jx - 1]
 * 即与当前字符构成匹配的数量加上当前位置之前全部匹配的数量。
 * 而如果条件不成立，则简单更新
 *     count[ix][jx] = count[ix][jx - 1]
 * 这样，循环结束后，count 数组的最后一个元素就是要求的结果。
 * 
 * 后来看了看《算法笔记》上面的解答，感觉思路好像要更简单一些，并且也是一个
 * O(n) 算法，是统计每个位置前面的 P 的数量以及后面的 T 的数量。对于每一个
 * A，只要将两者相乘，即可得与当前位置匹配的 PAT 的数量，将这些乘积求和即可。
 */

int main(){
	string str;
	cin >> str;
	int len = str.size();
	string p = "PAT";
	vector<vector<long long>> count(4, vector<long long>(len + 1, 0));
	count[0].assign(len + 1, 1);
	for(int ix = 1; ix <= 3; ++ix){
		for(int jx = 1; jx <= len; ++jx){
			if(p[ix - 1] == str[jx - 1])
				count[ix][jx] += count[ix-1][jx-1] + count[ix][jx - 1];
			else
				count[ix][jx] = count[ix][jx - 1];
			if(count[ix][jx] > CONST)
				count[ix][jx] %= CONST;
		}
	}
	/*
	for(auto v : count){
        for(long long e : v)
            cout << e << ' ';
        cout << endl;
	}*/
	cout << count[3][len] << endl;
	return 0;
}
