#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * 这个题一开始肯定要做一些预处理，把两个矩阵每列的交集计算出来，
 * 只是需要注意重复的情况，一开始我就是犯了这个错误。
 *
 * 然后我的策略其实就是直接暴力 dfs，毕竟最多也才只有 7000+ 种
 * 情况，用 dfs 的效率倒也不差。这里写 dfs 的时候我还 debug 挺
 * 久的，可见太久没写还是不熟悉了。
 *
 * 此题更高效的算法就是像紫书一样建立一个编码树，我因为觉得太复
 * 就没有这样做。实际上，这里并不需要真的建树啊，只是采用树的
 * 逻辑而已。感觉写起来逻辑还要比 dfs 简单，一会儿说不定试试。
 */

#define VERSION2
#ifdef  VERSION1

char one[6][6], two[6][6], tmp[6];
vector<vector<char>> candidate(5);

void dfs(int pos, int &k){
	for(int ix = 0; ix != candidate[pos].size(); ++ix){
		tmp[pos] = candidate[pos][ix];
		if(pos == 4) --k;
		else dfs(pos + 1, k);
		if(k == 0) break;
	}
}

int main(){
	//freopen("1.out", "w", stdout);
	int T, k, max;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &k);
		for(int ix = 0; ix != 5; ++ix)
			candidate[ix].clear();
		for(int ix = 0; ix != 6; ++ix)
			scanf("%s", one[ix]);
		for(int ix = 0; ix != 6; ++ix)
			scanf("%s", two[ix]);
		for(int ix = 0; ix != 5; ++ix)
		for(int jx = 0; jx != 6; ++jx)
		for(int kx = 0; kx != 6; ++kx)
			if(one[jx][ix] == two[kx][ix]){
				candidate[ix].push_back(one[jx][ix]);
				for(int lx = kx; lx != 6; ++lx)
					if(two[lx][ix] == one[jx][ix])
						two[lx][ix] = '-';
				break;
			}
		max = 1;
		for(int ix = 0; ix != 5; ++ix)
			max = max * candidate[ix].size();
		if(k > max){
			printf("NO\n");
			continue;
		}
		for(int ix = 0; ix != 5; ++ix){
			sort(candidate[ix].begin(), candidate[ix].end());
			/*for(char ch : candidate[ix])
				printf("%c", ch);
			printf("\n");*/
		}
		dfs(0, k);
		printf("%s\n", tmp);
	}
	return 0;
}

#else

//VERSION 2

int  cnt[5];
char one[6][6], two[6][6], ans[6];
vector<vector<char>> candidate(5);

int main(){
	//freopen("1.out", "w", stdout);
	int T, k, max;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &k);
		for(int ix = 0; ix != 5; ++ix)
			candidate[ix].clear();
		for(int ix = 0; ix != 6; ++ix)
			scanf("%s", one[ix]);
		for(int ix = 0; ix != 6; ++ix)
			scanf("%s", two[ix]);
		for(int ix = 0; ix != 5; ++ix)
		for(int jx = 0; jx != 6; ++jx)
		for(int kx = 0; kx != 6; ++kx)
			if(one[jx][ix] == two[kx][ix]){
				candidate[ix].push_back(one[jx][ix]);
				for(int lx = kx; lx != 6; ++lx)
					if(two[lx][ix] == one[jx][ix])
						two[lx][ix] = '-';
				break;
			}
		max = 1;
		for(int ix = 0; ix != 5; ++ix)
			max = max * candidate[ix].size();
		if(k > max){
			printf("NO\n");
			continue;
		}
		for(int ix = 0; ix != 5; ++ix)
			sort(candidate[ix].begin(), candidate[ix].end());
		cnt[4] = 1;
		for(int ix = 3; ix >= 0; --ix) 
			cnt[ix] = cnt[ix+1] * candidate[ix+1].size();
		for(int ix = 0, jx; ix != 5; ++ix){
			for(jx = 0; k > cnt[ix]; ++jx) k -= cnt[ix];
			ans[ix] = candidate[ix][jx];
		}
		printf("%s\n", ans);
	}
	return 0;
}

#endif
