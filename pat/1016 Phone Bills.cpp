#include <stdio.h>
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <algorithm>
using namespace std;
struct node{
	string time;
	int timestamp;
	bool state;
	bool friend operator<(node node1, node node2){
		return node1.timestamp < node2.timestamp;
	}
};
float count_bill(string start, string end, int rate[24]){
	float cost = 0;
	int day1, day2, hour1, hour2, minute1, minute2;
	day1 = stoi(start.substr(3, 2));
	hour1 = stoi(start.substr(6, 2));
	minute1 = stoi(start.substr(9));
	day2 = stoi(end.substr(3, 2));
	hour2 = stoi(end.substr(6, 2));
	minute2 = stoi(end.substr(9));
	while(day1 != day2 || hour1 != hour2){
		cost += rate[hour1] * (60 - minute1);
		if (++hour1 == 24) {
			hour1 = 0;
			++day1;
		}
		minute1 = 0;
	}
	cost += rate[hour1] * (minute2 - minute1);
	return cost / 100;
}
int main(){
	int toll[24];
	for (int ix = 0; ix < 24; ix++)
		scanf("%d", &toll[ix]);
	int N;
	scanf("%d", &N);
	map<string, set<node>> bills;
	node onenode;
	string name, time, state, online("on-line");
	int day, hour, minute;
	for(int ix = 0; ix != N; ix++){
		cin >> name >> time >> state;
		day = stoi(time.substr(3, 2));
		hour = stoi(time.substr(6, 2));
		minute = stoi(time.substr(9));
		onenode.time = time;
		onenode.timestamp = 1440 * day + 60 * hour + minute;
		onenode.state = (state == "on-line");
		bills[name].insert(onenode);
	}
	set<node>::iterator next;
	float cost, total;
	for(auto It = bills.begin(); It != bills.end(); It++){
		total = 0;
		for (auto setit = It->second.begin(); setit != It->second.end();) {
			cost = 0;
			next = setit;
			next++;
			if (next == It->second.end()) break;
			if(setit->state == 1 && next ->state == 0) {
				if(!total) cout << It->first << " " << (It->second.begin())->time.substr(0, 2) << endl;
				cost = count_bill(setit->time, next->time, toll);
				total += cost;
				cout << setit->time.substr(3) << " " << next->time.substr(3);
				printf(" %d $%.2f\n", next->timestamp - setit->timestamp, cost);
				setit = ++next;
			}
			else ++setit;
		}
		if(total) printf("Total amount: $%.2f\n", total);
	}
	system("pause");
	return 0;
}
