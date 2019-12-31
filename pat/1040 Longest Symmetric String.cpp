#include <iostream>
#include <string>

using namespace std;

/*
 * 这个题的思路是挺巧妙的，是从内到外寻找这样一个对称子串。
 * 需要注意的是，根据中心位置的不同，可以分为2n+1种情况，
 * 即n个字符和n+1个字符之间的空隙，其中最边缘的四种情况可
 * 以不予考虑，所以一共是2n-3种情况。最坏情况下算法的时间
 * 复杂度是O(n^2)，平均情况下仅为O(n)而已。
 */

int main(){
	string input;
	getline(cin, input);
	int maxlen = 1, len = input.length();
	int curr, left, right, currlen;
	for(int ix = 2; ix < 2*len - 1; ++ix){
		if(ix & 1){//if ix is odd
			currlen = 1;
			curr = ix >> 1;
			left = curr - 1;
			right = curr + 1;
		}
		else{//if ix is even
			currlen = 0;
			right = ix >> 1;
			left = right - 1;
		}
		while (left >= 0 && right < len && input[left] == input[right]) {
			currlen += 2;
			left--;
			right++;
		}
		if (currlen > maxlen) maxlen = currlen;
	}
	cout << maxlen << endl;
	system("pause");
	return 0;
}
