#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
	string one, two;
	vector<int> countone(26, 0), counttwo(26, 0);
	vector<int> featureone, featuretwo;
	while(cin >> one >> two){
		for(char ch : one)
			countone[ch - 'A']++;
		for(char ch : two)
			counttwo[ch - 'A']++;
		for(int e : countone)
			if(e != 0)
				featureone.push_back(e);
		for(int e : counttwo)
			if(e != 0)
				featuretwo.push_back(e);
		sort(featureone.begin(), featureone.end());
		sort(featuretwo.begin(), featuretwo.end());
		if(featureone == featuretwo)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
        featureone.clear();
        featuretwo.clear();
        fill(countone.begin(), countone.end(), 0);
        fill(counttwo.begin(), counttwo.end(), 0);
	}
	return 0;
}
