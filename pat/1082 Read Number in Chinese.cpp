#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

/*
 * 这个题确实很难啊，感觉逻辑很复杂，就算是我柳神的代码也跟
 * 我的似的充满了修修补补，一点都不优雅。对于该题有两个思路
 * 
 * 一开始的思路是逐位遍历输入的数字，遇到非零的数字则将对应
 * 的拼音以及单位输出，遇到连续的零则只输出一个零。这种方案
 * 不能解决一些特殊情况，比如 101000 这种是不输出零的，以及
 * 100001000 不输出 Wan，我觉得我的问题还是对中文读数字的
 * 方式不够熟悉。尽管如此，这种方案也 AC 了，PAT的数据确实
 * 不行。
 *
 * 后来采用的思路感觉更严谨，即对输入进行分节，分别读出各节，
 * 然后再把每节串接起来，实际处理起来控制逻辑也比较繁琐，比如
 * 各节之间 ling 的添加，以及空格的添加，都比较复杂。最终还是
 * 修修补补写出来了，第一种思路不能解决的问题都可以解决了！
 */

#define VERSION2

string units[4] = {" Qian", " Bai", " Shi", ""};
string digits[10] = {"ling", "yi", "er", "san", "si",
                     "wu", "liu", "qi", "ba", "jiu"};

string getUnit(int count){
	return units[count];
}

#ifdef VERSION1

string getUnit(int count);

int main(){
	string input, res;
	cin >> input;

	int len = input.length(), count = len, ix = 0;
	bool zeroflag = false;
	if(input.front() == '-'){
        res.append("Fu ");
        ++ix, --count;
	}

	//remove prefix zero
    while(ix < len - 1 && input[ix] == '0'){++ix, --count;}

    res.append(digits[input[ix++] - '0']);
    res.append(getUnit(count--));

	for(; ix != len; ++ix, --count){
		if(input[ix] != '0'){
			if(zeroflag){
                res.append(" ling");
                zeroflag = false;
			}
			res.push_back(' ');
			res.append(digits[input[ix] - '0']);
			res.append(getUnit(count));
		}
		else{
            if(count == 5 || count == 9)
                res.append(getUnit(count));
            else zeroflag = true;
        }
	}
	cout << res << endl;
	return 0;
}

#else

string read(string& origin){
	string res;
	int ix = 0;
	while(origin[ix] == '0') ++ix;
	bool zeroflag = false;
	if(ix == 4) return res;
	res.append(digits[origin[ix] - '0']);
    res.append(getUnit(ix));
    ++ix;
	while(ix < 4){
		if(origin[ix] != '0'){
			if(zeroflag){
                res.append(" ling");
                zeroflag = false;
			}
			res.push_back(' ');
			res += digits[origin[ix] - '0'] + getUnit(ix);
		}
		else zeroflag = true;
		++ix;
	}
	return res;
}

int main(){
	string input, res;
	cin >> input;
	if(input[0] == '-'){
		res.append("Fu ");
		input.erase(input.begin());
	}
	input.insert(input.begin(), 9 - input.size(), '0');

	string wan, ge;
	wan = input.substr(1, 4);
	ge = input.substr(5, 4);

	if(input[0] != '0'){
		res += digits[input[0] - '0'];
		res += " Yi";
		if(wan[0] == '0' && wan != "0000")
			res.append(" ling");
	}
    if(res.size() > 3 && wan != "0000")
        res.push_back(' ');
	wan = read(wan);
	res.append(wan);
	if(!wan.empty()) res.append(" Wan");
	if(res.size() > 3 && ge[0] == '0' && ge != "0000")
		res.append(" ling");
    if(res.size() > 3 && ge != "0000")
        res.push_back(' ');
	res.append(read(ge));
	if(res.empty()) res.append("ling");
	cout << res << endl;
	return 0;
}

#endif
