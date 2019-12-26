#include <stdio.h>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
struct node{
	int left, right;
	int value;
};
int main(){
	int N;
	scanf("%d", &N);
	vector<node> binTree(N);
	vector<int> keys(N);
	for(int ix = 0; ix != N; ix++){
		scanf("%d %d", &binTree[ix].left, &binTree[ix].right);
	}
	for(int ix = 0; ix != N; ix++){
		scanf("%d", &keys[ix]);
	}
	sort(keys.rbegin(), keys.rend());
	stack<int> unvisited;
	int pos = 0;
	while (pos != -1 || !unvisited.empty()) {
		while (pos != -1) {
			unvisited.push(pos);
			pos = binTree[pos].left;
		}
		pos = unvisited.top();
		unvisited.pop();
		binTree[pos].value = keys.back();
		keys.pop_back();
		pos = binTree[pos].right;
	}
	queue<int> layer;
	layer.push(0);
	printf("%d", binTree[0].value);
	while(!layer.empty()){
		pos = layer.front();
		layer.pop();
		if(pos != 0) printf(" %d", binTree[pos].value);
		if (binTree[pos].left  != -1) layer.push(binTree[pos].left);
		if (binTree[pos].right != -1) layer.push(binTree[pos].right);
	}
	system("pause");
	return 0;
}
