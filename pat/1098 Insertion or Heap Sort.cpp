#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
	int N;
	scanf("%d", &N);
	vector<int> intVec(N), partial(N);
	for(int ix = 0; ix != N; ix++){
		scanf("%d", &intVec[ix]);
	}
	for (int ix = 0; ix != N; ix++) {
		scanf("%d", &partial[ix]);
	}
	// insertiong sort
	vector<int> insertion(intVec);
	vector<int>::iterator local;
	int value;
	for(auto It = insertion.begin()+1; It != insertion.end(); It++){
		local = It;
		value = *It;
		while (local != insertion.begin() && value < *(local - 1)) {
			*local = *(local - 1);
			--local;
		}
		*local = value;
		if(insertion == partial){
			printf("Insertion Sort\n");
			local = It + 1;
			value = *local;
			while (local != insertion.begin() && value < *(local - 1)) {
				*local = *(local - 1);
				--local;
			}
			*local = value;
			printf("%d", insertion.front());
			for_each(insertion.cbegin() + 1, insertion.cend(), [](int element) {printf(" %d", element); });
			system("pause");
			return 0;
		}
	}
	// heap sort
	vector<int> heap(intVec);
	make_heap(heap.begin(), heap.end());
	for(int ix = 0; ix != N; ix++){
		pop_heap(heap.begin(), heap.end() - ix);
		if(heap == partial){
			printf("Heap Sort\n");
			pop_heap(heap.begin(), heap.end() - ix - 1);
			printf("%d", heap.front());
			for_each(heap.cbegin() + 1, heap.cend(), [](int element) {printf(" %d", element); });
			break;
		}
	}
	system("pause");
	return 0;
}
