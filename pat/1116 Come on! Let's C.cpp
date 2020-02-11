#include <map>
#include <string>
#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;

int isPirme(int num){
	for(int ix = 2; ix < sqrt(num) + 1; ++ix)
		if(num % ix == 0)
			return false;
	return true;
}

struct entry{
	string award;
	bool checked = false;
	entry(string str = ""): award(str){}
};

int main(){
	int N;
	scanf("%d", &N);
	map<int, entry> dataset;
	int curr;
	scanf("%d", &curr);
	dataset[curr] = entry("Mystery Award");
	for(int ix = 2; ix <= N; ++ix){
		scanf("%d", &curr);
		if(isPirme(ix))
			dataset[curr] = entry("Minion");
		else
			dataset[curr] = entry("Chocolate");
	}
	int K, query;
	scanf("%d", &K);
	while(K--){
		scanf("%d", &query);
		if(dataset.find(query) == dataset.end())
			printf("%d: Are you kidding?\n", query);
		else if(dataset[query].checked)
			printf("%04d: Checked\n", query);
		else{
			dataset[query].checked = true;
			printf("%04d: ", query);
			cout << dataset[query].award << endl;
		}
	}
	return 0;
}
