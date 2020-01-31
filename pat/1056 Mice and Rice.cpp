#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

vector<int> weights, fail_round;
vector<int> winner, order, r, Rank;

bool cmp(int one, int two){
	return fail_round[one] > fail_round[two];
}

int main(){
	int Np, Ng;
	scanf("%d %d", &Np, &Ng);
	weights.reserve(Np);
	order.reserve(Np);
	r.reserve(Np);
	Rank = vector<int>(Np, 0);
	fail_round = vector<int>(Np, 0);

	int curr, count, max, maxpos;
	for(int ix = 0; ix != Np; ++ix){
		scanf("%d", &curr);
		weights.push_back(curr);
	}
	for(int ix = 0; ix != Np; ++ix){
		scanf("%d", &curr);
		order.push_back(curr);
		r.push_back(ix);
	}

	while(true){
		max = -1, count = 0;
		for(int ix = 0; ix != order.size(); ++ix){
            curr = order[ix];
			if(weights[curr] > max){
				max = weights[curr];
				maxpos = curr;
			}
			if(++count == Ng){
				count = 0;
				winner.push_back(maxpos);
				max = -1;
				fail_round[maxpos]++;
			}
		}
		if(count != 0){
            winner.push_back(maxpos);
            fail_round[maxpos]++;
		}
		if(winner.size() == 1) break;
		order.assign(winner.begin(), winner.end());
		winner.clear();
	}

	sort(r.begin(), r.end(), cmp);

	Rank[r[0]] = 1;
	int prev = 1;
	for(int ix = 1; ix != Np; ++ix){
		if(fail_round[r[ix]] == fail_round[r[ix - 1]])
			Rank[r[ix]] = prev;
		else{
			Rank[r[ix]] = ix + 1;
			prev = ix + 1;
		}
	}
	printf("%d", Rank[0]);
	for(int ix = 1; ix != Np; ++ix)
		printf(" %d", Rank[ix]);
	printf("\n");
	return 0;
}
