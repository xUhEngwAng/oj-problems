#include <cstdio>
#include <cmath>

bool isPrime(int num){
	if(num == 1) return false;
	int end = sqrt(num);
	for(int ix = 2; ix <= end; ++ix)
		if(num % ix == 0) return false;
	return true;
}

int main(){
	int Msize, N;
	scanf("%d %d", &Msize, &N);
	while(!isPrime(Msize)) Msize++;
	const int m = Msize;
	bool *hash = new bool[m];
	int curr, pos;
	bool find;

	scanf("%d", &curr);
	pos = curr % m;
	hash[pos] = true;
	printf("%d", pos);

	for(int ix = 1; ix != N; ++ix){
		scanf("%d", &curr);
		find = false;
		for(int jx = 0; jx < ((m + 1) >> 1); ++jx){
			pos = (curr + jx * jx) % m;
			if(hash[pos] == false){
				hash[pos] = true;
				find = true;
				break;
			}
		}
		if(find) printf(" %d", pos);
		else     printf(" -");
	}
	printf("\n");
	return 0;
}
