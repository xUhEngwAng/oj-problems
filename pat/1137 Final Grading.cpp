#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

/*
 * 这个题还挺繁琐的，居然也一次 AC 了，佩服我自己。
 */

struct student{
	int Gp = -1;
	int Gmid = -1;
	int Gfinal = -1;
};

struct res_node{
	int Gp;
	int Gmid;
	int Gfinal;
	int final;
	string name;
	res_node() = default;
	res_node(int Gp, int Gmid, int Gfinal, int final, string name):
	Gp(Gp), Gmid(Gmid), Gfinal(Gfinal), final(final), name(name){}
};

vector<res_node> res;

bool cmp(int one, int two){
	if(res[one].final != res[two].final)
		return res[one].final > res[two].final;
	return res[one].name < res[two].name;
}

int main(){
	int P, M, N;
	cin >> P >> M >> N;
	map<string, student> data;
	string curr;
	int score;
	for(int ix = 0; ix != P; ++ix){
		cin >> curr >> score;
		if(score < 200) continue;
		data[curr] = student();
		data[curr].Gp = score;
	}
	map<string, student>::iterator it;
	for(int ix = 0; ix != M; ++ix){
		cin >> curr >> score;
		if((it = data.find(curr)) == data.end())
			continue;
		it->second.Gmid = score;
	}
	double dfinal;
	int ifinal;
	for(int ix = 0; ix != N; ++ix){
		cin >> curr >> score;
		if((it = data.find(curr)) == data.end())
			continue;
		it->second.Gfinal = score;
		if(it->second.Gmid > score)
			dfinal = 0.4 * it->second.Gmid + 0.6 * score;
		else
			dfinal = score;
		ifinal = (int)dfinal;
		if(dfinal - ifinal >= 0.5) ifinal++;
		if(ifinal >= 60)
			res.emplace_back(it->second.Gp, it->second.Gmid,
				             score, ifinal, it->first);
	}

	vector<int> order(res.size());
	for(int ix = 0; ix != order.size(); ++ix)
		order[ix] = ix;
	sort(order.begin(), order.end(), cmp);
	for(int e : order){
		cout << res[e].name   << ' ' << res[e].Gp << ' ' << res[e].Gmid << ' '
		     << res[e].Gfinal << ' ' << res[e].final << endl;
	}
	return 0;
}
