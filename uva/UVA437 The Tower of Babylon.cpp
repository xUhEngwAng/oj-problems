#include <cstdio>
#include <unordered_map>
#include <map>
using namespace std;

struct entry{
	int cur_height;
	int max_height = 0;
};

map<pair<int, int>, entry> info;
pair<int, int> tmp;

int dfs(pair<int, int> key){
	if(info[key].max_height != 0)
		return info[key].max_height;

	int max_height = 0, curr;
	for(auto it = info.begin(); it != info.end(); ++it){
		tmp = it->first;
		if((tmp.first < key.first && tmp.second < key.second) ||
		   (tmp.second < key.first && tmp.first < key.second)){
			curr = dfs(it->first);
			if(curr > max_height)
				max_height = curr;
		}
	}
	info[key].max_height = max_height + info[key].cur_height;
	return info[key].max_height;
}

int main(){
	int n, cnt = 1;
	int x, y, z, max, curr;
	while(scanf("%d", &n) == 1){
		if(n == 0) break;
		printf("Case %d: maximum height = ", cnt++);
		info.clear();
		for(int ix = 0; ix != n; ++ix){
			scanf("%d %d %d", &x, &y, &z);
			tmp.first = x, tmp.second = y;
			if(info.find(tmp) == info.end() || info[tmp].cur_height < z) 
				info[tmp].cur_height = z;
			tmp.second = z;
			if(info.find(tmp) == info.end() || info[tmp].cur_height < y) 
				info[tmp].cur_height = y;
			tmp.first = y;
			if(info.find(tmp) == info.end() || info[tmp].cur_height < x) 
				info[tmp].cur_height = x;
		}
		max = 0;
		for(auto it = info.begin(); it != info.end(); ++it){
			curr = dfs(it->first);
			if(curr > max) max = curr;
		}
		printf("%d\n", max);
	}
	return 0;
}
