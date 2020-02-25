#include <cstring>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

/*
 * 简单说一下我的思路吧。对于每一个查询，如果都需要遍历所有
 * 数据的话，那么整体的时间复杂度就是 O(n * k)，在极端情况
 * 下，n = 10,000, k = 80,000，这就是 800 ms，已经超时了。
 * 所以对于每一个查询，都需要在 O(logn) 的时间内给出结果。
 *
 * 我的思路是分别对每个车牌号进行处理，将它的出入信息按照时间
 * 排序，利用其中相匹配的信息来更新该车的总泊车时间，并且将
 * 这些合法的出入时间以及出或者入的状态保存到一个向量当中。
 * 完成对所有车牌的处理后，按照时间升序将此向量排序，通过一
 * 次遍历即可获得其中所有时间节点，校园中的泊车总量。对于一个
 * 查询，只需用二分查找，找到恰好小于该查询时间的泊车数量即可。
 */

struct entry{
	char plate_num[8];
	int  time;
	int  isin = 0;

	bool operator<(const entry& right){
		int res = strcmp(plate_num, right.plate_num);
		if(res == 0)
			return time < right.time;
		return res < 0;
	}
};

struct parking_time{
	char plate_num[8];
	int  time;
	parking_time() = default;
	parking_time(char *num, int t): time(t){
		strcpy(plate_num, num);
	}

	bool operator<(const parking_time &right) const {
		if(time != right.time)
			return time > right.time;
		return strcmp(plate_num, right.plate_num) < 0;
	}
};

struct parking_cnt{
	int time;
	int cnt;
	parking_cnt() = default;
	parking_cnt(int t, int c): time(t), cnt(c){}
	bool operator<(const parking_cnt &right) const {
		return time < right.time;
	}
};

entry *data;
vector<parking_time> park_time;
vector<parking_cnt> park_cnt;
vector<parking_cnt>::iterator it;

int main(){
	int n, k, currtime, max;
	scanf("%d %d", &n, &k);
	data = new entry[n];

	char plate_num[8], status[4], prev_num[8];
	int hr, minu, snd;
	for(int ix = 0; ix != n; ++ix){
		scanf("%s %d:%d:%d %s", plate_num, &hr, &minu, &snd, status);
		strcpy(data[ix].plate_num, plate_num);
		data[ix].time = hr * 3600 + minu * 60 + snd;
		if(strcmp(status, "in") == 0) data[ix].isin = 1;
	}
	sort(data, data + n);
	for(int ix = 0, jx; ix != n; ){
		strcpy(plate_num, data[ix].plate_num);
		currtime = 0;
		for(jx = ix; jx != n; ++jx)
			if(strcmp(plate_num, data[jx].plate_num) != 0)
				break;
		while(true){
			while(ix < jx && data[ix].isin == 0) ++ix;
			if(ix == jx) break;
			while(ix + 1 < jx && data[ix + 1].isin == 1) ++ix;
			if(ix == jx - 1){
				++ix;
				break;
			}
			currtime += data[ix + 1].time - data[ix].time;
			park_cnt.emplace_back(data[ix].time, 1);
			park_cnt.emplace_back(data[ix + 1].time, -1);
			++ix;
		}
		park_time.emplace_back(plate_num, currtime);
	}
	park_cnt.emplace_back(-1, 0);
	sort(park_cnt.begin(), park_cnt.end());
	for(int ix = 1; ix != park_cnt.size(); ++ix)
		park_cnt[ix].cnt += park_cnt[ix - 1].cnt;
	sort(park_time.begin(), park_time.end());
	while(k--){
		scanf("%d:%d:%d", &hr, &minu, &snd);
		currtime = hr * 3600 + minu * 60 + snd;
		it = upper_bound(park_cnt.begin(), park_cnt.end(), parking_cnt(currtime, 0)) - 1;
		printf("%d\n", it->cnt);
	}
	printf("%s", park_time[0].plate_num);
	max = park_time.front().time;
	for(int ix = 1; ix != park_time.size(); ++ix){
		if(park_time[ix].time != max) break;
		printf(" %s", park_time[ix].plate_num);
	}
	snd = max % 60;
	max = (max - snd) / 60;
	minu = max % 60;
	hr = (max - minu) / 60;
	printf(" %02d:%02d:%02d\n", hr, minu, snd);
	return 0;
}
