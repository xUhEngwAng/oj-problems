#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(){
	freopen("1.out", "w", stdout);
	int N, cnt = 0;
	int up, down;
	bool flag;
	string one, two, str;
	while(true){
		scanf("%d", &N);
		if(N == 0) break;
		if(cnt++ != 0) printf("\n");
		flag = false;
		for(down = 1234; ; down++){
			up = down * N;
			one = to_string(down);
			two = to_string(up);
			if(two.size() == 4) continue;
			if(two.size() > 5) break;
			if(one.size() == 4) one.push_back('0');
			str = one + two;
			sort(str.begin(), str.end());
			if(str == "0123456789"){
				printf("%d / %05d = %d\n", up, down, N);
				flag = true;
			}
		}
		if(!flag) printf("There are no solutions for %d.\n", N);
	}//
	return 0;
}
