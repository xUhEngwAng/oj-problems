#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <set>
using namespace std;

struct word{
	string str;
	bool flag;    //delete flag

	word(string s = ""): str(s), flag(false){}
};

string to_lower_sort(string str){
	int m = str.length();
	for (int i = 0; i != m; ++i)
		if (str[i] <= 'Z')
			str[i] = str[i] - 'A' + 'a';
	sort(str.begin(), str.end());
	return str;
}

int main(){
	map<string, word> dict;
	string str, lower;
	map<string, word>::iterator it;
	while(true){
		cin >> str;
		if(str == "#") break;
		lower = to_lower_sort(str);
		if((it = dict.find(lower)) == dict.end())
			dict[lower] = word(str);
		else
			it->second.flag = true;
	}
	set<string> res;
	for(it = dict.begin(); it != dict.end(); ++it)
		if(it->second.flag == false)
			res.insert(it->second.str);
	for(string s : res)
		cout << s << endl;
	return 0;
}
