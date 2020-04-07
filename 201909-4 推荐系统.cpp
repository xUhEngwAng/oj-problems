#include <unordered_map>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct tuple_{
	int type, commodity, score;
	tuple_() = default;
	tuple_(int t, int c, int s): type(t), commodity(c), score(s){}
	bool operator<(const tuple_ &right){
		if(score == right.score)
			if(type == right.type)
				return commodity < right.commodity;
			else
				return type < right.type;
		return score > right.score;
	}
};

vector<unordered_map<int, int>> goods;
vector<vector<int>> res;
vector<int> query_num;
vector<tuple_> seq;

int main(){
	int m, n;
	scanf("%d %d", &m, &n);
	goods.resize(m);
	query_num.resize(m);
	res.resize(m);
	//seq.reserve(5000000);
	int id, score;
	for(int ix = 0; ix != n; ++ix){
		scanf("%d %d", &id, &score);
		for(int jx = 0; jx != m; ++jx)
			goods[jx][id] = score;
	}
	int num, cmd, type, commodity, K;
	scanf("%d", &num);
	while(num--){
		scanf("%d", &cmd);
		if(cmd == 1){
			scanf("%d %d %d", &type, &commodity, &score);
			goods[type][commodity] = score;
		}else
		if(cmd == 2){
			scanf("%d %d", &type, &commodity);
			goods[type].erase(commodity);
		}
		else{
			scanf("%d", &K);
			for(int ix = 0; ix != m; ++ix){
				scanf("%d", &query_num[ix]);
				res[ix].clear();
			}
			seq.clear();
			for(int ix = 0; ix != m; ++ix)
				for(auto it = goods[ix].begin(); it != goods[ix].end(); ++it)
					seq.emplace_back(ix, it->first, it->second);
			sort(seq.begin(), seq.end());
			for(int ix = 0; ix != seq.size(); ++ix){
				if(query_num[seq[ix].type]){
					res[seq[ix].type].push_back(seq[ix].commodity);
					query_num[seq[ix].type]--;
					K--;
					if(K == 0) break;
				}
			}
			for(auto v : res){
				if(v.empty()) printf("-1");
				else printf("%d", v[0]);
				for(int ix = 1; ix < v.size(); ++ix)
					printf(" %d", v[ix]);
				printf("\n");
			}
		}
	}
	return 0;
}
