#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

struct entry{
	int egrade;
	int igrade;
	int total;
	int id;

	entry(): egrade(0), igrade(0){}

	bool operator<(entry two){
		if(total != two.total)
			return total > two.total;
		return egrade > two.egrade;
	}

	bool operator==(entry two){
		return egrade == two.egrade && igrade == two.igrade;
	}
};

int main(){
	int N, M, K;
	scanf("%d %d %d", &N, &M, &K);
	int *quota = new int[M];
	for(int ix = 0; ix != M; ++ix)
		scanf("%d", quota + ix);
	entry *datas = new entry[N];
	vector<vector<int>> choices(N, vector<int>(K));
	for(int ix = 0; ix != N; ++ix){
		scanf("%d %d", &datas[ix].egrade, &datas[ix].igrade);
		datas[ix].total = datas[ix].egrade + datas[ix].igrade;
		datas[ix].id = ix;
		for(int jx = 0; jx != K; ++jx)
			scanf("%d", &choices[ix][jx]);
	}

	sort(datas, datas + N);

	vector<entry> lastAdmit(M);
	vector<vector<int>> admission(M);
	int currChoice, currid;
	for(int ix = 0; ix != N; ix++){
        currid = datas[ix].id;
		for(int jx = 0; jx != K; ++jx){
			currChoice = choices[currid][jx];
			if(quota[currChoice] > 0 || datas[ix] == lastAdmit[currChoice]){
				quota[currChoice]--;
				lastAdmit[currChoice].egrade = datas[ix].egrade;
				lastAdmit[currChoice].igrade = datas[ix].igrade;
				admission[currChoice].push_back(currid);
				break;
			}
		}
	}

	for(int ix = 0; ix != M; ++ix){
		sort(admission[ix].begin(), admission[ix].end());
		if(!admission[ix].empty()){
			printf("%d", admission[ix].front());
			for(auto it = admission[ix].begin() + 1; it != admission[ix].end(); ++it)
				printf(" %d", *it);
		}
		printf("\n");
	}
	return 0;
}
