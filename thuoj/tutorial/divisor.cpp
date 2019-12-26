#include <iostream>
#define MAX(X, Y) ((X) > (Y)? (X): (Y))
#define MIN(X, Y) ((X) < (Y)? (X): (Y))
int main(){
	int a, b, x;
	std::cin >> a >> b;
	if(a < b){
		x = b;b = a;a = x;
	}
	while(x = a % b){
		a = MAX(b, x);
		b = MIN(b, x);
	}
	std::cout << b;
	return 0;
}
