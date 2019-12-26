#include <stdio.h>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
using namespace std;
int main(){
	int N, M;
	scanf("%d", &N);
	if (N == 0) return 0;
	scanf("%d", &M);
	map<int, vector<int>> tree;
	int K, node;
	vector<int> child;
 	for(int ix = 0; ix != M; ix++){
		scanf("%d %d", &node, &K);
		child.clear();
		child.resize(K);
		for (int jx = 0; jx != K; jx++)
			scanf("%d", &child[jx]);
		tree[node] = child;
	}
	int currNum = 1, nextNum = 0, count = 0, leafcount = 0, pos;//indicating the end of each layer
	queue<int> intque;
	intque.push(1);
	while(!intque.empty()){
		pos = intque.front();
		intque.pop();
		if (tree.find(pos) != tree.end()) {
			nextNum += tree[pos].size();
			for (auto It = tree[pos].cbegin(); It != tree[pos].cend(); It++)
				intque.push(*It);
		}
		else leafcount += 1;
		count += 1;
		if(count == currNum){
			if (pos == 1) printf("%d", leafcount);
			else{
				printf(" %d", leafcount);
			}
			count = 0;
			leafcount = 0;
			currNum = nextNum;
			nextNum = 0;
		}
	}
	return 0;
}