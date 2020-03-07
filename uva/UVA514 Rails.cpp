#include <vector>
#include <cstdio>
using namespace std;

int main(){
	int n, curr, cnt;
	vector<int> seq, stack;
	while(scanf("%d", &n) == 1){
		if(n == 0) break;
		seq.resize(n);
		while(true){
			scanf("%d", &curr);
			if(curr == 0) break;
			seq[0] = curr;
			for(int ix = 1; ix != n; ++ix)
				scanf("%d", &seq[ix]);
			cnt = 0;
			for(int ix = 1; ix <= n;)
				if(!stack.empty() && stack.back() == seq[cnt]){
					stack.pop_back();
					cnt++;
				}
				else stack.push_back(ix++);
			while(!stack.empty() && stack.back() == seq[cnt]){
				stack.pop_back();
				++cnt;
			}
			if(stack.empty()) printf("Yes\n");
			else printf("No\n");
			stack.clear();
		}
		printf("\n");
	}
	return 0;
}
