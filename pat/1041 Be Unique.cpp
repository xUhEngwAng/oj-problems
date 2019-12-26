#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
int main_slow_version(){
	int N;
	scanf("%d", &N);
	vector<int> bets(N);
	for (int ix = 0; ix != N; ix++)
		scanf("%d", &bets[ix]);
	for(auto It= bets.begin(); It != bets.end(); It++){
		if (count(bets.begin(), bets.end(), *It) == 1){
			printf("%d", *It);
			system("pause");
			return 0;
		}
	}
	printf("None");
	system("pause");
	return 0;
}

int main(){
	int N;
	scanf("%d", &N);
	vector<int> bets(N);
	map<int, int> count;
	for (int ix = 0; ix != N; ix++) {
		scanf("%d", &bets[ix]);
		count[bets[ix]]++;
	}
	for (auto It = bets.begin(); It != bets.end(); It++){
		if(count[*It] == 1){
			printf("%d", *It);
			system("pause");
			return 0;
		}
	}
	printf("None");
	system("pause");
	return 0;
}