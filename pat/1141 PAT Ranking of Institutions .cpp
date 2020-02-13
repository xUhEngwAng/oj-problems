#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

/*
 * 这个题本身非常常规，没有任何难度，不过是一个 stl 水题而已。
 * 不过做的过程中也学到了一些知识。
 *
 * 由于数据量比较大，我比较担心会用 iostream 和 string 会超
 * 时，所以一开始是用的 char* 来表示学校 id。然后整体数据结构
 * 是一个从 char* 到 struct school 的map，来保存各个学校的
 * 信息。这次我已经长了教训，直到每次输入之前都要为的 char* 
 * 重新分配内存空间，否则 map 会将不同输入的 char* 视作相同。
 *
 * 然而我忽略了另一个问题，由于每次都分配了不同的内存空间，那么
 * 无论每次输入的 schoolid 是何值，map 都不会将它们视作相同，
 * 因为这里的键值本质上是这个字符串的起始地址啊，所以每次输入都
 * 不同。最后无奈，我还是换回了我喜欢的 string 和 iostream，就
 * 没有这个问题了。万幸，没有超时。
 */

struct school{
	double score = 0;
	int num = 0;
};

struct res_node{
	string schoolid;
	int score;
	int num;

	res_node(string name, int score, int n):
	schoolid(name), score(score), num(n){}

};

void to_lower(string &str){
	for(int ix = 0; ix != str.size(); ++ix)
		str[ix] = tolower(str[ix]);
}

vector<res_node> res;

bool cmp(int one, int two){
	if(res[one].score != res[two].score)
		return res[one].score > res[two].score;
	if(res[one].num != res[two].num)
		return res[one].num < res[two].num;
	return res[one].schoolid < res[two].schoolid;
}

int main(){
	int N, score;
	double wscore;
	cin >> N;
	string testeeid, schoolid;
	map<string, school> data;
	for(int ix = 0; ix != N; ++ix){
		cin >> testeeid >> score >> schoolid;
		if(testeeid[0] == 'B') wscore = score / 1.5;
		else if(testeeid[0] == 'A') wscore = score;
		else wscore = score * 1.5;
		to_lower(schoolid);
		if(data.find(schoolid) == data.end())
			data[schoolid] = school();
		data[schoolid].num++;
		data[schoolid].score += wscore;
	}

	for(auto it = data.begin(); it != data.end(); ++it)
		res.emplace_back(it->first, (int)it->second.score, it->second.num);
	vector<int> order(res.size());
	for(int ix = 0; ix != order.size(); ++ix)
		order[ix] = ix;
	sort(order.begin(), order.end(), cmp);

	cout << order.size() << endl;
	int prevRank = 1;
	cout << "1 " << res[order[0]].schoolid << ' '
		 << res[order[0]].score << ' ' << res[order[0]].num << endl;
	for(int ix = 1; ix < order.size(); ++ix){
		if(res[order[ix]].score != res[order[ix - 1]].score)
			prevRank = ix + 1;
		cout << prevRank << ' ' << res[order[ix]].schoolid << ' '
		     << res[order[ix]].score << ' ' << res[order[ix]].num << endl;

	}
	return 0;
}
