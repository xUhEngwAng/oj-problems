#include <vector>
#include <stack>
#include <cstdio>
#include <algorithm>
using namespace std;

/*
 * 第一次写并查集，没想到还蛮简单的。我使用的策略是在 find
 * 函数中进行路径压缩，使用一个栈来实现非常方便。
 */

vector<int> ufs(1001, -1);
vector<vector<int>> clusters(1001);

int find(int num){
	stack<int> s;
	int res = num;
	while(ufs[res] != -1){
		s.push(res);
		res = ufs[res];
	}
	while(!s.empty()){
		ufs[s.top()] = res;
		s.pop();
	}
	return res;
}

void uni(int left, int right){
	int one = find(left);
	int two = find(right);
	if(one == two) return;
	ufs[two] = one;
	for(int e : clusters[two])
		clusters[one].push_back(e);
	clusters[two].clear();
}

int main(){
	int N, num, curr, target;
	scanf("%d", &N);
	for(int ix = 1; ix <= N; ++ix){
		scanf("%d: %d", &num, &curr);
		target = find(curr);
		clusters[target].push_back(ix);
		while(--num){
			scanf("%d", &curr);
			uni(target, curr);
		}
	}

	vector<int> res;
	for(auto v : clusters)
		if(v.size())
			res.push_back(v.size());

	sort(res.rbegin(), res.rend());
	printf("%d\n%d", res.size(), res.front());
	for(int ix = 1; ix != res.size(); ++ix)
		printf(" %d", res[ix]);
	return 0;
}
