#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
class point{
public:
	int x;
	int y;
};
int main(){
	int n;
	scanf("%d", &n);
	point* houses = new point[n];
	for(int ix = 0; ix != n; ++ix){
		scanf("%d %d", &houses[ix].x, &houses[ix].y);
	}
	int count = 0;
	for(int ix = 0; ix != n - 1; ++ix){
		for(int jx = ix + 1; jx != n; ++jx){
			if ((houses[jx].x > houses[ix].x &&
				 houses[jx].y > houses[ix].y) ||
			    (houses[jx].x < houses[ix].x &&
				 houses[jx].y < houses[ix].y))
				++count;
		}
	}
	printf("%d", count);
	while (getchar() != ' ');
	return 0;
}
