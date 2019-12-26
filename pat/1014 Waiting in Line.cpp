#include <stdio.h>
#include <vector>
#include <deque>
#include <algorithm>
#define MAX 65535
using namespace std;
struct node{
	int usrid;
	int beginTime;
	int processTime;
};
struct querynode{
	int usrid;
	int finishtime;
	int beginTime;
};
auto find_queue(vector<deque<node>> &service){
	vector<deque<node>>::size_type minlen = 100;
	vector<deque<node>>::iterator minpos;
	for(auto It = service.begin(); It != service.end(); It++){
		if (It->size() < minlen){
			minlen = It->size();
			minpos = It;
			if (minlen == 0) break;
		}
	}
	return minpos;
}
int main(){
	int N, M, K, Q;
	scanf("%d %d %d %d", &N, &M, &K, &Q);
	vector<deque<node>> service(N);
	vector<deque<node>>::iterator pos;
	deque<node> outside;
	int processTime;
	node currUsr;
	for(int ix = 0; ix != K; ix++){
		scanf("%d", &processTime);
		currUsr.usrid = ix + 1;
		currUsr.processTime = processTime;
		pos = find_queue(service);
		if(pos->size() == M){//service already full
			outside.push_back(currUsr);
			for(++ix; ix != K; ix++){
				scanf("%d", &processTime);
				currUsr.usrid = ix + 1;
				currUsr.processTime = processTime;
				outside.push_back(currUsr);
			}
			break;
		}
		if (ix < N) currUsr.beginTime = 0;
		pos->push_back(currUsr);
	}
	vector<querynode> query(Q);
	vector<querynode>::iterator target;
	for(int ix = 0; ix != Q; ix++){
		scanf("%d", &query[ix].usrid);
	}
	int currTime = 0, minTime, processed;
	for(int count = 0; count != query.size();){
		minTime = MAX;
		for(auto It = service.begin(); It != service.end(); It++){
			if (It->empty()) continue;
			if (It->front().processTime < minTime) minTime = It->front().processTime;
		}
		currTime += minTime;
		for (auto It = service.begin(); It != service.end(); It++){
			if (It->empty()) continue;
			if (It->front().processTime == minTime) {
				processed = It->front().usrid;
				if ((target = find_if(query.begin(), query.end(), 
					[processed](querynode oneEntry) {return oneEntry.usrid == processed; })) != query.end()){
					target->finishtime = currTime;
					target->beginTime = It->front().beginTime;
					count++;
				}
				It->pop_front();
				if (It->empty()) continue;
				It->front().beginTime = currTime;
			}
			else It->front().processTime -= minTime;
		}
		while(!outside.empty()){
			pos = find_queue(service);
			if (pos->size() == M) break;
			currUsr = outside.front();
			outside.pop_front();
			pos->push_back(currUsr);
		}
	}
	int hour, minute;
	for(auto It = query.begin(); It != query.end(); It++){
		if(It->beginTime < 540){
			hour = It->finishtime / 60 + 8;
			minute = It->finishtime % 60;
			printf("%02d:%02d\n", hour, minute);
		}
		else printf("Sorry\n");
	}
	system("pause");
	return 0;
}

