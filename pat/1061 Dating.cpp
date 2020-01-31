#include <string>
#include <iostream>
using namespace std;

/*
 * 这个题有毒，题意一点都不清楚。比如第一个出现的大写字母必须
 * 要在 A ~ G 的范围内，这是题目没有说明的；再比如，题目上说
 * 小时由第二个相同的**字符**给出，然而给的测试用例中，E是第
 * 三个相同的字符了！
 * 建议不要做这个题。
 */

string days[7] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};

int main(){
	string one, two;
	int day, hour;
	cin >> one >> two;
	int ix = 0;
	while(true){
		if(one[ix] == two[ix] && one[ix] >= 'A' && one[ix] <= 'G')
			break;
		++ix;
	}
	day = one[ix++] - 'A';
	while(true){
		if(one[ix] == two[ix])
			if((one[ix] >= 'A' && one[ix] <= 'N') || isdigit(one[ix]))
                break;
		++ix;
	}
	if(isdigit(one[ix])) hour = one[ix] - '0';
	else hour = 10 + one[ix] - 'A';
	string h = to_string(hour);
	if(h.size() == 1) h.insert(h.begin(), '0');

	cin >> one >> two;
	ix = 0;
	while(true){
		if(one[ix] == two[ix] && isalpha(one[ix]))
			break;
		++ix;
	}
	string minute = to_string(ix);
	if(minute.size() == 1) minute.insert(minute.begin(), '0');
	cout << days[day] << ' ' << h << ':' << minute << endl;
	return 0;
}
