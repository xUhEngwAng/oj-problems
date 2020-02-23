#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define MIN(X, Y) ((X) < (Y)? (X): (Y))

int main(){
	int N, curr, strong, total, count = 1;
	bool endflag;
	vector<int> secret, guess;
	vector<int> secret_hash, guess_hash;
	while(scanf("%d", &N) == 1){
		if(N == 0) break;
		printf("Game %d:\n", count++);
		secret.resize(N);
		guess.resize(N);
		secret_hash.assign(10, 0);
		for(int ix = 0; ix != N; ++ix){
			scanf("%d", &curr);
			secret[ix] = curr;
			secret_hash[curr]++;
		}
		while(true){
			endflag = true;
			guess_hash.assign(10, 0);
			for(int ix = 0; ix != N; ++ix){
				scanf("%d", &curr);
				if(curr != 0) endflag = false;
				guess[ix] = curr;
				guess_hash[curr]++;
			}
			if(endflag) break;
			strong = total = 0;
			for(int ix = 0; ix != N; ++ix)
				if(secret[ix] == guess[ix])
					++strong;
			for(int ix = 0; ix != 10; ++ix)
				total += MIN(secret_hash[ix], guess_hash[ix]);
			printf("    (%d,%d)\n", strong, total - strong);
		}
	}
	return 0;
}
