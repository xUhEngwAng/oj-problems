#include <algorithm>
#include <vector>
#include <stdio.h>
using namespace std;
int main(){
	int N, b;
	scanf("%d %d", &N, &b);
	vector<int> reverse;
	while(N != 0){
		reverse.push_back(N % b);
		N = N / b;
	}
	vector<int> origin(reverse.rbegin(), reverse.rend());
	if (origin == reverse) printf("Yes\n");
	else printf("No\n");
	printf("%d", origin[0]);
	for_each(origin.begin() + 1, origin.end(), [](int bit) {printf(" %d", bit); });
	system("pause");
	return 0;
}
