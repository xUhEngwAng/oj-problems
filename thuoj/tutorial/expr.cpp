#include <iostream>
int main(){
	char oper;
	long long a, b, c;
	std::cin >> a >> oper >> b;
	switch(oper){
	case '+':
		c = a + b;
		break;
	case '-':
		c = a - b;
		break;
	case '*':
		c = a * b;
		break;
	}
	std::cout << c;
	return 0;
}
