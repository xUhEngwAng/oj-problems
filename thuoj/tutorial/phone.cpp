#include <cstdio>
int main(){
	int h1, m1, s1;
	int h2, m2, s2;
	scanf("%d:%d:%d", &h1, &m1, &s1);
	scanf("%d:%d:%d", &h2, &m2, &s2);
	int result = 3600 * (h2 - h1) + 60 * (m2 - m1) + s2 - s1;
	if (result < 0) result += 86400;
	printf("%d", result);
	return 0;
}
