#include <unordered_map>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

int n, m;

struct query{
	int left, right;
	int a, b;
};

unordered_map<int, int> cnt;
query queries[100000];
int arr[100001], num_digit[100000], num_value[100000];
int order[100000];

bool cmp(int one, int two){
	int num_group = sqrt(n + 0.5);
	int group1 = queries[one].left / num_group;
	int group2 = queries[two].left / num_group;
	if(group1 == group2){
		if(group1 & 1) return queries[one].right < queries[two].right;
		else return queries[one].right > queries[two].right;
	}
	return group1 < group2;
}

void add(int pos){
    if(cnt.find(arr[pos]) == cnt.end()) cnt[arr[pos]] = 1;
	else cnt[arr[pos]]++;
}

void del(int pos){
	cnt[arr[pos]]--;
	if(cnt[arr[pos]] == 0) cnt.erase(arr[pos]);
}

int main(){
	scanf("%d %d", &n, &m);
	for(int ix = 1; ix <= n; ++ix)
		scanf("%d", arr + ix);
	for(int ix = 0; ix != m; ++ix)
		scanf("%d %d %d %d",  &queries[ix].left, &queries[ix].right,
			   &queries[ix].a, &queries[ix].b);
	for(int ix = 0; ix != m; ++ix)
		order[ix] = ix;
	sort(order, order + m, cmp);
	int l = 1, r = 0, ql, qr, digit_cnt, value_cnt, a, b;
	for(int ix = 0; ix != m; ++ix){
		ql = queries[order[ix]].left;
		qr = queries[order[ix]].right;
		a  = queries[order[ix]].a;
		b  = queries[order[ix]].b;
		while(l < ql) del(l++);
		while(l > ql) add(--l);
		while(r < qr) add(++r);
		while(r > qr) del(r--);
		digit_cnt = value_cnt = 0;
		//printf("%d:\n", order[ix]);
		for(auto it = cnt.begin(); it != cnt.end(); ++it){
            //printf("%d %d\n", it->first, it->second);
			if(it->first <= b && it->first >= a){
				digit_cnt += it->second;
				value_cnt++;
			}
		}
		//printf("\n");
		num_digit[order[ix]] = digit_cnt;
		num_value[order[ix]] = value_cnt;
	}
	for(int ix = 0; ix != m; ++ix)
		printf("%d %d\n", num_digit[ix], num_value[ix]);
	return 0;
}
