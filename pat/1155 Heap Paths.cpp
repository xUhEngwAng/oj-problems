#include <stdio.h>
#include <vector>
using namespace std;
vector<int> heap;
vector<int> paths;
int heaptype;
void dfs(int start){
	paths.push_back(heap[start]);
	unsigned left, right;
	left = start * 2;
	right = left + 1;
	if(left >= heap.size()){//hit the bottom
		if(heaptype == 1){
			for (auto It = paths.cbegin(); It != paths.cend() - 1; It++) {
				if (*(It + 1) > *It) {
					heaptype = 0;
					break;
				}
			}
		}else if(heaptype == 2){
			for (auto It = paths.cbegin(); It != paths.cend() - 1; It++) {
				if (*(It + 1) < *It) {
					heaptype = 0;
					break;
				}
			}
		}
		printf("%d", paths.front());
		for (auto It = paths.cbegin() + 1; It != paths.cend(); It++)
			printf(" %d", *It);
		printf("\n");
		paths.pop_back();
		return;
	}
	if (right < heap.size()) dfs(right);
	dfs(left);
	paths.pop_back();
}
int main(){
	int N;
	scanf("%d", &N);
	heap.resize(N + 1);
	for (int ix = 1; ix != N + 1; ix++)
		scanf("%d", &heap[ix]);
	if (heap[1] > heap.back()) heaptype = 1;
	else heaptype = 2;
	dfs(1);
	if (heaptype == 1) printf("Max Heap");
	else if (heaptype == 2) printf("Min Heap");
	else printf("Not Heap");
	system("pause");
	return 0;
}
