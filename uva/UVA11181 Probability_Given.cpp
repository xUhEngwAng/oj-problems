#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

/*
 * 这个题是相当有意思的。题目是说，有 N 个独立的事件，它们各自
 * 发生的概率分别是 p1, p2, ..., pN，求在发生了 r 个事件的条件
 * 下，各个事件发生的概率。
 *
 * 利用条件概率公式，需要求到 P(r) 以及 P(Xi, r)，这样有
 *
 * P(Xi | r) = P(Xi, r) / P(r)
 *
 * 为了求到 P(r)，可以枚举所有 N 个事件中 r 个事件的组合，将所有
 * 这些组合中的事件发生，而其他事件不发生的概率加起来就可以了。而
 * 为了求到 P(Xi, r)，可以在上面的枚举中，将各个组合发生的概率（
 * 而组合外的事件不发生的概率）维护到组合包含的各个事件中。这样，
 * 一次 dfs 就可以搞定问题了。
 */

int n, r;
double p[21], cond_prob[21];
double curr_prob, pr;
vector<int> seq;

void dfs(int curr){
	seq.push_back(curr);
	curr_prob = curr_prob * p[curr];
	if(seq.size() == r + 1){
		pr += curr_prob;
		for(int e : seq)
			cond_prob[e] += curr_prob;
		goto ret;
	}
	for(int ix = curr + 1; ix <= n; ++ix)
		dfs(ix);
	ret:
	seq.pop_back();
	curr_prob = curr_prob / p[curr];
}

int main(){
	int round = 1;
	double temp;
	while(scanf("%d %d", &n, &r) == 2){
		if(n == 0 && r == 0) break;
		printf("Case %d:\n", round++);
		curr_prob = p[0] = 1.0;
		for(int ix = 1; ix <= n; ++ix){
			scanf("%lf", &temp);
			curr_prob *= (1 - temp);
			p[ix] = temp / (1 - temp);
		}
		memset(cond_prob, 0, sizeof(cond_prob));
		seq.clear();
		pr = 0.0;
		dfs(0);
		//printf("%f\n", pr);
		for(int ix = 1; ix <= n; ++ix)
			printf("%.6f\n", cond_prob[ix] / pr);
	}
	return 0;
}
