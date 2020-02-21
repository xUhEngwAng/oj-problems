#include <vector>
#include <cstring>
#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;

/*
 * 这个题非常有内涵啊！我尝试了好多好多方法，终于没有超时了。
 *
 * 对于这种查询类型的题，我的基本思路都是首先对数据进行预处理，
 * 得到每个可能查询都需要的结果，这样对于每一个查询，在 O(1)
 * 的时间内就可以得到需要的结果，直接输出就好。因此，对于每个
 * 级别的考试，我分别管理了一个向量；此外还引入一个向量来保存
 * 所有的考场信息；最后一个查询是比较复杂的，我的实现是用一个
 * map<int, vector> 将日期映射到存储该日期所有考场信息的向量
 * 中。然而我这种方案超时了。
 *
 * 于是我把代码中所有出现的 string 和 cin/cout 都换掉，自己
 * 手写了 stoi 的 c-style 版本，结果直接快了五倍有余！这也太
 * 夸张了吧！没想到 string 和 cin/cout 居然这么慢。
 *
 * 之后看了看柳神的代码，发现更绝。柳神的代码不到50行，我看了看
 * 我的150行代码，默默留下了泪水......柳神都不是预处理的思路，
 * 而是对于每一个 query，都进行现场查询，还用了 string 以及
 * cin/cout，我提交一下，耗时还特别短，我的眼泪就止不住往下流。
 *
 * 然后柳神代码里的一个关键是用 unordered_map 来存储某个日期
 * 所有 site 信息，而用 map 则会超时。这个我就觉得更神奇了，题
 * 目中至多只能有 900 个地点，log(900) < 10 而已，居然会带来
 * 如此大的影响。而 unordered_map 的底层使用 hashtable 来实现
 * 的，具体说来 hash_function 是对某一个很大的质数做模余，冲突
 * 解决方案采用独立链法，如果 site 的取值只是在 101 - 900 之间，
 * 则每次只需要 O(1) 的时间就可以访问到目标桶。
 *
 * 于是我又再次回顾我自己的代码，我是用 map<int, vector> 来存储
 * 每个日期对应的 site 信息的，为了对某个 site 信息进行更新，需
 * 遍历至多 900 个元素，这样就直接是 900 * 10000 的开销，也难怪
 * 超时了。但是我把 map<int, vector> 中的向量换成了散列，结果还
 * 是超时......我只能猜想是因为分配了太多内存空间，而消耗的时间吧。
 */

int stoi(char *str, int n){
    int res = 0;
    for(int ix = 0; ix < n; ++ix){
        res = res * 10;
        res += str[ix] - '0';
    }
    return res;
}

struct testee_info{
	char number[14];
	int score;
	testee_info() = default;
	testee_info(char *num, int s): score(s){strcpy(number, num);}
};

struct site_info{
	int numoftestee = 0;
	int totalscore = 0;
};

struct date_info{
	int site_num;
	int numoftestee;
	date_info() = default;
	date_info(int site, int num): site_num(site), numoftestee(num){}
	bool operator<(const date_info &right){
		if(numoftestee == right.numoftestee)
			return site_num < right.site_num;
		return numoftestee > right.numoftestee;
	}
};

vector<testee_info> basic, advanced, top;
vector<site_info> site(900);
map<int, vector<date_info>> date;
vector<date_info>::iterator it;

bool cmp1(int left, int right){
	if(basic[left].score == basic[right].score)
		return strcmp(basic[left].number, basic[right].number) < 0;
	return basic[left].score > basic[right].score;
}

bool cmp2(int left, int right){
	if(advanced[left].score == advanced[right].score)
		return strcmp(advanced[left].number, advanced[right].number) < 0;
	return advanced[left].score > advanced[right].score;
}

bool cmp3(int left, int right){
	if(top[left].score == top[right].score)
		return strcmp(top[left].number, top[right].number) < 0;
	return top[left].score > top[right].score;
}

int main(){
	int N, M, score, sitenum, currdate;
	scanf("%d %d", &N, &M);
	char *num;
	for(int ix = 0; ix != N; ++ix){
        num = new char[14];
		scanf("%s %d", num, &score);
		if(num[0] == 'B')
			basic.emplace_back(num, score);
		else if(num[0] == 'A')
			advanced.emplace_back(num, score);
		else
			top.emplace_back(num, score);
		sitenum = stoi(num + 1, 3) - 100;
		site[sitenum].numoftestee++;
		site[sitenum].totalscore += score;

		currdate = stoi(num + 4, 6);
		if(date.find(currdate) == date.end())
			date[currdate] = vector<date_info>();
		for(it = date[currdate].begin(); it != date[currdate].end(); ++it)
			if(it->site_num == sitenum){
				it->numoftestee++;
				break;
			}
		if(it == date[currdate].end())
			date[currdate].emplace_back(sitenum, 1);
	}
	vector<int> basic_order, advanced_order, top_order;
	for(int ix = 0; ix != basic.size(); ++ix)
		basic_order.push_back(ix);
	for(int ix = 0; ix != advanced.size(); ++ix)
		advanced_order.push_back(ix);
	for(int ix = 0; ix != top.size(); ++ix)
		top_order.push_back(ix);
	sort(basic_order.begin(), basic_order.end(), cmp1);
	sort(advanced_order.begin(), advanced_order.end(), cmp2);
	sort(top_order.begin(), top_order.end(), cmp3);

	//for(auto iter = date.begin(); iter != date.end(); ++iter)
	//	sort(iter->second.begin(), iter->second.end());

	int type;
	char *term;
	for(int ix = 1; ix <= M; ++ix){
        term = new char[7];
		scanf("%d %s", &type, term);
        printf("Case %d: %d %s\n", ix, type, term);
		switch(type){
			case 1:
			if(term[0] == 'B')
				if(basic.empty())
                    printf("NA\n");
				else
				for(int e : basic_order)
					printf("%s %d\n", basic[e].number, basic[e].score);
			else if(term[0] == 'A')
				if(advanced.empty())
					printf("NA\n");
				else
				for(int e : advanced_order)
					printf("%s %d\n", advanced[e].number, advanced[e].score);
			else
				if(top.empty())
					printf("NA\n");
				else
				for(int e : top_order)
					printf("%s %d\n", top[e].number, top[e].score);
			break;

			case 2:
				sitenum = stoi(term, 3) - 100;
				if(site[sitenum].numoftestee == 0)
					printf("NA\n");
				else
				printf("%d %d\n", site[sitenum].numoftestee, site[sitenum].totalscore);
			break;

			case 3:
				currdate = stoi(term, 6);
				if(date.find(currdate) == date.end())
					printf("NA\n");
				else{
					sort(date[currdate].begin(), date[currdate].end());
					for(auto entry: date[currdate])
						printf("%d %d\n", entry.site_num + 100, entry.numoftestee);
				}
			break;
		}
	}
	return 0;
}
