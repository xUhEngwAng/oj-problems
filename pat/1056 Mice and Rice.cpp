#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

/*
 * 这个题我做的也是够复杂的，开了好多个 vector。但是这里主要
 * 还是说明一下题意。
 * 一开始我是没能理解第三行输入的 order 是什么意思，还以为是
 * ix 第 order[ix] 个比赛，但是应该注意到 order[ix] 是可以
 * 等于零的，所以我的理解恰好反了。应该是 order[ix] 第 ix + 1
 * 个比赛才是（ix = 0, 1, 2, ...）
 * 然后在我的实现中还用了一个类似于表排序的方法，感觉还挺巧妙。
 */

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
