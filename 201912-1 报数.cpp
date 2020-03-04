#include <string>
#include <cstdio>
using namespace std;

bool isSkip(int num){
	if(num % 7 == 0) return true;
	string str = to_string(num);
	if(str.find('7') != -1) return true;
	return false;
}

int main(){
	int n, cnt = 0, skip[4] = {0, 0, 0, 0};
	scanf("%d", &n);
	int player = 0, curr = 1;
	while(true){
		if(isSkip(curr)) skip[player]++;
		else
		if(++cnt == n) break;
		if(++player == 4) player = 0;
		++curr;
	}
	printf("%d\n%d\n%d\n%d\n", skip[0], skip[1], skip[2], skip[3]);
	return 0;
}
