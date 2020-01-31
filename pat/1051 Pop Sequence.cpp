#include <stack>
#include <cstdio>
using namespace std;

int main(){
	int N, M, K;
	scanf("%d %d %d", &M, &N, &K);
	stack<int> s;
	int curr, count, *arr;
	arr = new int[N];
	while(K--){
		count = 1;
		for(int ix = 0; ix != N; ++ix)
			scanf("%d", arr + ix);
        for(int ix = 0; ix != N; ++ix){
            curr = arr[ix];
			while(s.empty() || s.top() != curr){
				s.push(count++);
				if(s.size() > M || s.size() > N) goto res;
			}
			s.pop();
		}
		res:
		if(s.empty()) printf("YES\n");
		else printf("NO\n");
		while(!s.empty()) s.pop();
	}
	return 0;
}
