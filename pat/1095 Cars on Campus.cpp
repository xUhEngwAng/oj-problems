#include <algorithm>
#include <map>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

enum Status{IN, OUT};

int computeTime(char t[9]){
    int time, second, minute, hour;
    second = t[7] - '0' + 10 * (t[6] - '0');
    minute = t[4] - '0' + 10 * (t[3] - '0');
    hour   = t[1] - '0' + 10 * (t[0] - '0');
    time = second + 60 * minute + 3600 * hour;
    return time;
}

void printTime(int time){
    int second, minute, hour;
    second = time % 60;
    time -= second;
    time /= 60;
    minute = time % 60;
    time -= minute;
    hour = time / 60;

    printf("%02d:%02d:%02d", hour, minute, second);
}

struct entry{
	int time;
	Status s;

	entry() = default;
	entry(char* t, char* status){
		if(strcmp(status, "in") == 0)
			s = IN;
		else s = OUT;
		time = computeTime(t);
	}

	bool operator<(entry two){
		return time < two.time;
	}
};

struct park_time{
	int time;
	char number[8];

	park_time(char* n, int t){
		time = t;
		strcpy(number, n);
	}

	bool operator<(park_time two){
		if(time != two.time)
			return time > two.time;
		return strcmp(number, two.number) < 0;
	}
};

int main(){
	int N, K;
	scanf("%d %d", &N, &K);
	map<string, vector<entry>> datas;
	char number[8], time[9], status[4];
	for(int ix = 0; ix != N; ++ix){
		scanf("%s %s %s", number, time, status);
		datas[string(number)].emplace_back(time, status);
	}

	for(auto e : datas){
        auto info = e.second;
        printf("%s: ", e.first);
        for(auto entry : info){
            printTime(entry.time);
            printf(" ");
        }
        printf("\n");
	}

	vector<park_time> park;
	park.reserve(datas.size());
	vector<int> in_time, out_time;
	in_time.reserve(N);
	out_time.reserve(N);

	int time_len;
	vector<entry> entries;
	for(auto e : datas){
		time_len = 0;
		entries = e.second;
		sort(entries.begin(), entries.end());
		for(auto it = entries.begin(); it != entries.end(); ++it){
			if(it->s == OUT) continue;
			if(it == entries.end() - 1) continue;
			if((it + 1)->s == IN) continue;
			time_len += (it + 1)->time - it->time;
			in_time.push_back(it->time);
			out_time.push_back((it + 1)->time);
			++it;
		}
		park.emplace_back(e.first, time_len);
	}

	sort(in_time.begin(), in_time.end());
	sort(out_time.begin(), out_time.end());

	char query[9];
	int query_time;
	for(int ix = 0; ix != K; ++ix){
		scanf("%s", query);
		query_time = computeTime(query);
		int lo = lower_bound(in_time.begin(), in_time.end(), query_time) - in_time.begin();
		int hi = lower_bound(out_time.begin(), out_time.end(), query_time) - out_time.begin();
		printf("%d\n", hi - lo);
	}

	make_heap(park.begin(), park.end());
	time_len = park.front().time;
	while(!park.empty() && park.front().time == time_len){
		printf("%s ", park.front().number);
		pop_heap(park.begin(), park.end());
		park.pop_back();
	}
	printTime(time_len);
	return 0;
}
