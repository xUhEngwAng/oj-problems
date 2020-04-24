#include <cstdio>
#include <stack>
#include <string>
using namespace std;

char equa[8];

int calc(int one, int two, char op){
	if(op == '+') return one + two;
	else if(op == '-') return one - two;
	else if(op == 'x') return one * two;
	else return one / two;
}

int evaluate(char equa[]){
	stack<int> digit;
	stack<char> op;
	int res = 0, one, two;
	for(int ix = 0; ix != 7; ++ix){
		if(isdigit(equa[ix])) digit.push(equa[ix] - '0');
		else{
			while(!(op.empty() ||
			   (op.top() == '+' || op.top() == '-') &&
			   (equa[ix] == 'x' || equa[ix] == '/'))){
				two = digit.top();
				digit.pop();
				one = digit.top();
				digit.pop();
				digit.push(calc(one, two, op.top()));
				op.pop();
			}
			op.push(equa[ix]);
		}
	}
	while(!op.empty()){
		two = digit.top();
		digit.pop();
		one = digit.top();
		digit.pop();
		digit.push(calc(one, two, op.top()));
		op.pop();
	}
	return digit.top();
}

int main(){
	int n, res;
	scanf("%d", &n);
	for(int ix = 0; ix != n; ++ix){
		scanf("%s", equa);
		res = evaluate(equa);
		//printf("%d\n", res);
		if(res == 24) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
