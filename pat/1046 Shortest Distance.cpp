#include <stdio.h>
#include <vector>
#include <algorithm>
#include <numeric>
#define MIN(X,Y) ((X)>(Y)?(Y):(X))
#define MAX(X,Y) ((X)>(Y)?(X):(Y))
using namespace std;
int main() {
	int N, M, first, second, sum = 0, tmp;
	scanf("%d", &N);
	vector<int> distances(N);
	for (int ix = 0; ix != N - 1; ix++) {
		scanf("%d", &tmp);
		distances[ix + 1] = distances[ix] + tmp;
	}
	scanf("%d", &tmp);
	sum = tmp + distances[N-1];
	scanf("%d", &M);
	int dist, pos1, pos2;
	for (int ix = 0; ix != M; ix++) {
		scanf("%d %d", &pos1, &pos2);
		first = MIN(pos1 - 1, pos2 - 1);
		second = MAX(pos1 - 1, pos2 - 1);
		dist = distances[second] - distances[first];
		printf("%d\n", MIN(dist, sum - dist));
	}
	system("pause");
	return 0;
}
