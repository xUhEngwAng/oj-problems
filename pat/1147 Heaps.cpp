#include <cstdio>
#include <vector>
using namespace std;

#define LEFTCHILD(X)  (X << 1)
#define RIGHTCHILD(X) ((X << 1) + 1)

int *arr, N;
vector<int> seq;

bool gt(int left, int right){return left > right;}
bool lt(int left, int right){return left < right;}
bool (*cmp)(int left, int right);
bool testHeap(int root){
	int lc= LEFTCHILD(root);
	int rc = RIGHTCHILD(root);
	if(lc <= N && !cmp(arr[root], arr[lc]))
		return false;
	if(rc <= N && !cmp(arr[root], arr[rc]))
		return false;
	bool res = true;
	if(lc <= N){
		res = testHeap(lc);
		if(!res) return false;
	}
	if(rc <= N)
		res = testHeap(rc);
	return res;
}

void postOrder(int root){
	if(LEFTCHILD(root) <= N) postOrder(LEFTCHILD(root));
	if(RIGHTCHILD(root) <= N) postOrder(RIGHTCHILD(root));
	seq.push_back(arr[root]);
}

int main(){
	int M;
	scanf("%d %d", &M, &N);
	arr = new int[N + 1];
	bool res;
	while(M--){
		for(int ix = 1; ix <= N; ++ix)
			scanf("%d", arr + ix);
		if(arr[1] > arr[2]) cmp = gt;
		else                cmp = lt;
		res = testHeap(1);
		if(!res) printf("Not Heap\n");
		else
		if(arr[1] > arr[2]) printf("Max Heap\n");
		else                printf("Min Heap\n");
		postOrder(1);
		printf("%d", seq.front());
		for(int ix = 1; ix < N; ++ix)
			printf(" %d", seq[ix]);
		printf("\n");
		seq.clear();
	}
	return 0;
}
