#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
struct node{
	int arrive;
	int process;
};
int main(){
	int N, K;
	scanf("%d %d", &N, &K);
	vector<node> queue;
	int hour, minute, second, processTime, count = 0;
	node curruser;
	for(int ix = 0; ix != N; ix++){
		scanf("%d:%d:%d %d", &hour, &minute, &second, &processTime);
		curruser.arrive  = hour * 3600 + minute * 60 + second;
		if (curruser.arrive > 17 * 3600) continue;
		curruser.process = processTime * 60;
		queue.push_back(curruser);
		count++;
	}
	sort(queue.begin(), queue.end(), [](node usr1, node usr2) {return usr1.arrive > usr2.arrive; });

	//for_each(queue.begin(), queue.end(), [](node oneNode) {printf("%d ", oneNode.arrive); });
	int currTime = 8 * 3600, elapsed;
	float waitingTime = 0;
	vector<int> pqueue(K);
	vector<int>::iterator vacant;
	make_heap(pqueue.begin(), pqueue.end(), greater<int>());
	while(1){
		while(!queue.empty() && (vacant = find(pqueue.begin(),pqueue.end(),0)) != pqueue.end()){
			if(queue.back().arrive > currTime){//not have arrived yet
				elapsed = queue.back().arrive - currTime;
				currTime = queue.back().arrive;//time elapses
				for(auto It = pqueue.begin(); It != pqueue.end(); It++){
					*It = *It - elapsed;
					if (*It < 0) *It = 0;
				}
				make_heap(pqueue.begin(), pqueue.end(), greater<int>());
			}else{
				waitingTime += currTime - queue.back().arrive;
				*vacant = queue.back().process;
				make_heap(pqueue.begin(), pqueue.end(), greater<int>());
				queue.pop_back();
			}
		}
		if (queue.empty()) break;
		//for_each(pqueue.begin(), pqueue.end(), [](int usr) {printf("%d ", usr); });
		//printf("\n");
		currTime += *pqueue.begin();
		for (auto It = pqueue.rbegin(); It != pqueue.rend(); It++) {
			*It = *It - *pqueue.begin();
		}
		make_heap(pqueue.begin(), pqueue.end(), greater<int>());
		//for_each(pqueue.begin(), pqueue.end(), [](int usr) {printf("%d ", usr); });
	}
	printf("%.1f\n", waitingTime/(count*60));
	system("pause");
	return 0;
}