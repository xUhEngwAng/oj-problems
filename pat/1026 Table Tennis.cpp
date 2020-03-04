#include <algorithm>
#include <cstdio>
#include <vector>
#include <deque>
using namespace std;

/*
 * 此题算是一个比较大的模拟题了，但是整体思路还是简单的。
 *
 * 在数据结构方面，对每一张乒乓桌肯定都要保存一个变量，来存储
 * 它的相关状态信息，即它的类型，它服务的数量，以及当前的结束
 * 时间，这样可以通过比较结束时间以及当前时间来判断某张桌子是
 * 否空闲。对每一对球员也要管理相关的信息，即到达时间，开始服
 * 务的时间，他们是否是 VIP 等，统一放在一个向量当中。
 *
 * 引入一个队列来管理所有等待的球员。算法的整体思路如下：对于
 * 每一次循环，令当前时间加一（秒），首先判断当前时刻是否有新
 * 的球员到来，如果有，则将其加入等待队列中；随后对队列进行判
 * 断，如果队列非空，则试图找一张空闲的桌子进行分配，如果没有
 * 空闲桌子则退出本轮循环。
 *
 * 这里的关键在于球桌分配的算法，经过我对题意的抽象，可以描述
 * 如下：如果队列中存在 VIP 球员，且存在空闲的 VIP 球桌，则
 * 优先将该球桌分配给该对球员；否则，则将第一个空闲的球桌分配
 * 给队列首的球员。
 *
 * 然后记录一下做的过程中遇到的坑。其一是输出的格式，题目要求
 * 等待时间是上整（round up)，因此我的代码实现是
 *
 * wait_time = (serve_time - arrive_time + 59) / 60;
 *
 * 然而实际上它可能是想表达四舍五入？因为我改成 + 30 后一个
 * 测试点就通过了......
 *
 * 此外，按照题目的要求，playing time 是不超过两个小时的，我
 * 认为这是对输入数据的约束，没想到实际输入中可能出现超过两小
 * 时的情况，需要编码将其减小到两个小时......这样我就通过了。
 */

#define INF   (0x7fffffff)
#define BEGIN (28800)
#define END   (75600)

enum Type {VIP, NORMAL};

class Customer{
public:
	int arrive_time;
	int serve_time = INF;
	int play_time;
	Type ctype = NORMAL;
};

class Table{
public:
	int count = 0;
	int finish_time = BEGIN;
	Type ttype = NORMAL;
};

bool cmp1(const Customer &left, const Customer &right){
	return left.arrive_time < right.arrive_time;
}

bool cmp2(const Customer &left, const Customer &right){
	return left.serve_time < right.serve_time;
}

deque<int> q;
deque<int>::iterator it;
vector<Table> tables;
vector<Customer> info;

int find_table(int currtime){
	for(int ix = 1; ix != tables.size(); ++ix)
		if(tables[ix].finish_time <= currtime)
			return ix;
	return -1;
}

int find_vip_table(int currtime){
    for(int ix = 1; ix != tables.size(); ++ix)
		if(tables[ix].ttype == VIP && tables[ix].finish_time <= currtime)
			return ix;
	return -1;
}

deque<int>::iterator find_vip(){
	for(auto it = q.begin(); it != q.end(); ++it)
		if(info[*it].ctype == VIP)
			return it;
	return q.end();
}

void printTime(int time){
	int snd = time % 60;
	time = (time - snd) / 60;
	int minu = time % 60;
	int hr = (time - minu) / 60;
	printf("%02d:%02d:%02d", hr, minu, snd);
}

int main(){
	int N, hr, minu, snd, play_time, tag, arrive;
	scanf("%d", &N);
	info.resize(N);
	for(int ix = 0; ix != N; ++ix){
		scanf("%d:%d:%d %d %d", &hr, &minu, &snd, &play_time, &tag);
		arrive = hr * 3600 + minu * 60 + snd;
		info[ix].arrive_time = arrive;
		if(play_time > 120) play_time = 120;
		info[ix].play_time = play_time * 60;
		if(tag) info[ix].ctype = VIP;
	}
	int K, M, currtable, curr, viptable;
	scanf("%d %d", &K, &M);
	tables.resize(K + 1);
	while(M--){
		scanf("%d", &currtable);
		tables[currtable].ttype = VIP;
	}
	sort(info.begin(), info.end(), cmp1);
	/*for(auto c : info){
        printTime(c.arrive_time);
        printf(" %d %d\n", c.play_time, c.ctype);
	}*/
	int currtime = BEGIN, cnt = 0;
	while(currtime < END){
		if(cnt < N && info[cnt].arrive_time <= currtime)
			q.push_back(cnt++);
		while(!q.empty()){
			currtable = find_table(currtime);
			if(currtable == -1) break;
			it = find_vip();
			viptable = find_vip_table(currtime);
			if(it != q.end() && viptable != -1){
                curr = *it;
                currtable = viptable;
                q.erase(it);
			}else{
                curr = q.front();
                q.pop_front();
			}
			info[curr].serve_time = currtime;
			tables[currtable].finish_time = info[curr].play_time + currtime;
			tables[currtable].count++;
		}
        ++currtime;
	}
	sort(info.begin(), info.end(), cmp2);
	for(int ix = 0; ix != N; ++ix){
		if(info[ix].serve_time == INF) break;
		printTime(info[ix].arrive_time);
		printf(" ");
		printTime(info[ix].serve_time);
		printf(" %d\n", (info[ix].serve_time - info[ix].arrive_time + 30) / 60);
	}
	printf("%d", tables[1].count);
	for(int ix = 2; ix <= K; ++ix)
		printf(" %d", tables[ix].count);
	printf("\n");
	return 0;
}
