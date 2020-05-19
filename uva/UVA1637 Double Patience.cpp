#include <cstdio>
#include <stack>
#include <iostream>
using namespace std;

#define VERSION2
#ifdef  VERSION1

stack<char> piles[9];

double dfs(){
	bool flag = true;
	char tmp;
	double res = 0.0;
	int cnt = 0;

	for(int ix = 0; ix != 9; ++ix)
		if(!piles[ix].empty()){
			flag = false;
			break;
		}
	if(flag){return 1.0;}

	for(int ix = 0; ix != 8; ++ix){
		if(piles[ix].empty()) continue;
		for(int jx = ix + 1; jx != 9; ++jx){
			if(!piles[jx].empty() && 
				piles[ix].top() == piles[jx].top()){
				tmp = piles[ix].top();
				//printf("%c\n", tmp);
				//cin.ignore();
				piles[ix].pop();
				piles[jx].pop();
				res += dfs();
				piles[ix].push(tmp);
				piles[jx].push(tmp);
				cnt++;
			}
		}
	}
	if(cnt) return res / cnt;
	return 0;
}

int main(){
	char str[3];
	for(int ix = 0; ix != 9; ++ix)
		for(int jx = 0; jx != 4; ++jx){
			scanf("%s", str);
			piles[ix].push(str[0]);
		}
	double res = dfs();
	printf("%.6f\n", res);
	return 0;
}

#else

//VERSION2

int arr[9];
double dp[1953125];
int piles[9][4];

int hashcode(){
	int ret = arr[0];
	for(int ix = 1; ix != 9; ++ix){
		ret = ret * 5;
		ret += arr[ix];
	}
	return ret;
}

double dfs(){
	int hash = hashcode();
	if(dp[hash] != -1) return dp[hash];
	if(hash == 0){
		dp[hash] = 1.0;
		return dp[hash];
	}
	int cnt = 0;
	double res = 0.0;
	for(int ix = 0; ix != 8; ++ix){
		if(arr[ix] == 0) continue;
		for(int jx = ix + 1; jx != 9; ++jx){
			if(arr[jx] != 0 && 
			   piles[ix][arr[ix]-1] == piles[jx][arr[jx]-1]){
				arr[ix]--, arr[jx]--;
				res += dfs();
				arr[ix]++, arr[jx]++;
				cnt++;
			}
		}
	}
	if(cnt == 0) dp[hash] = 0.0;
	else         dp[hash] = res / cnt;
	return dp[hash];
}

int main(){
	char str[3];
	for(int ix = 0; ix != 9; ++ix)
		for(int jx = 0; jx != 4; ++jx){
			scanf("%s", str);
			piles[ix][jx] = str[0];
		}
	for(int ix = 0; ix != 9; ++ix) arr[ix] = 4;
	for(int ix = 0; ix != 1953125; ++ix) dp[ix] = -1;
	double res = dfs();
	printf("%.6f\n", res);
	return 0;
}

#endif
