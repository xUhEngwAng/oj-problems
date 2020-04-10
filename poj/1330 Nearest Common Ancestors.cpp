#include <cstdio>
#include <cstring>

int father[10001];
bool visited[10001];

int main(){
	int t, n, one, two, root;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		memset(father, 0, sizeof(int) * (n + 1));
		memset(visited, 0, sizeof(bool) * (n + 1));
		for(int ix = 0; ix != n - 1; ++ix){
			scanf("%d %d", &one, &two);
			father[two] = one;
		}
		scanf("%d %d", &one, &two);
		for(; one != 0; one = father[one])
			visited[one] = true;
		while(!visited[two]) two = father[two];
		printf("%d\n", two);
	}
	return 0;
}
