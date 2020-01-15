#include <vector>
#include <string>
#include <iostream>
using namespace std;

int main(){
	vector<int> count(128, 0);
	string str1, str2;
	cin >> str1 >> str2;
	for(auto ch : str1)
		count[ch]++;
	int missing_num = 0;
	for(auto ch : str2){
		if(count[ch] > 0) count[ch]--;
		else missing_num++;
	}
	if(missing_num == 0)
		cout << "Yes " << str1.size() - str2.size() << endl;
	else
		cout << "No " << missing_num << endl;
	return 0;
}
