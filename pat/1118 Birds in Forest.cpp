#include <stack>
#include <vector>
#include <cstdio>
using namespace std;

/*
 * 简单的并查集罢了。
 */

vector<int> unionfind(10001);

int find(int curr){
	stack<int> s;
	int res = curr;
	while(res != unionfind[res]){
		s.push(res);
		res = unionfind[res];
	}
	while(!s.empty()){
		curr = s.top();
		s.pop();
		unionfind[curr] = res;
	}
	return res;
}

void uni(int left, int right){
	int one = find(left);
	int two = find(right);
	unionfind[two] = one;
}

int main(){
	int N, count = 0, currcnt, root, curr;
	scanf("%d", &N);
	for(int ix = 1; ix != 10001; ++ix)
		unionfind[ix] = ix;
	for(int ix = 0; ix != N; ++ix){
		scanf("%d %d", &currcnt, &root);
		if(root > count) count = root;
		while(--currcnt){
			scanf("%d", &curr);
			uni(root, curr);
			if(curr > count) count = curr;
		}
	}
	int num = 0;
	for(int ix = 1; ix <= count; ++ix)
		if(unionfind[ix] == ix) ++num;
	printf("%d %d\n", num, count);

	int K, one, two;
	scanf("%d", &K);
	while(K--){
		scanf("%d %d", &one, &two);
		if(find(one) == find(two))
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}
