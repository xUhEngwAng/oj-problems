#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#include <stack>
using namespace std;
int main_slow_version(){
	int N;
	scanf("%d", &N);
	vector<int> stack, tmp;
	stack.reserve(N);
	char command[11];
	int value;
	for(int ix = 0; ix != N; ix++){
		scanf("%s", command);
		if(!strcmp(command, "Pop")){
			if (stack.empty()) {
				printf("Invalid\n");
			}else{
				value = stack.back();
				stack.pop_back();
				printf("%d\n", value);
			}
		}else
		if(!strcmp(command, "PeekMedian")){
			if (stack.empty()) {
				printf("Invalid\n");
			}else{
				tmp.assign(stack.begin(), stack.end());
				sort(tmp.begin(), tmp.end());
				if (tmp.size() % 2) printf("%d\n", tmp[tmp.size() / 2]);
				else printf("%d\n", tmp[tmp.size() / 2 - 1]);
			}
		}else{
			scanf("%d", &value);
			stack.push_back(value);
		}
	}
	system("pause");
	return 0;
}

int main_slow_version_2_0(){
	int N;
	scanf("%d", &N);
	vector<int> stack, tmp;
	multiset<int> sorted;
	stack.reserve(N);
	char command[11];
	int value;
	for (int ix = 0; ix != N; ix++) {
		scanf("%s", command);
		if (command[1] == 'o') {
			if (stack.empty()) {
				printf("Invalid\n");
			}
			else {
				value = stack.back();
				stack.pop_back();
				sorted.erase(sorted.find(value));
				printf("%d\n", value);
			}
		}
		else
			if (command[1] == 'e') {
				if (stack.empty()) {
					printf("Invalid\n");
				}
				else {
					tmp.assign(sorted.begin(), sorted.end());
					if (tmp.size() % 2) printf("%d\n", tmp[tmp.size() / 2]);
					else printf("%d\n", tmp[tmp.size() / 2 - 1]);
				}
			}
			else {
				scanf("%d", &value);
				stack.push_back(value);
				sorted.insert(value);
			}
	}
	system("pause");
	return 0;
}

#define LOWBIT(X) ((X)&(-X))
#define MAX 100001
int c[MAX] = { 0 };
void update(int x, int v){
	for(int ix = x; ix < MAX; ix += LOWBIT(ix)){
		c[ix] += v;
	}
}
int get_sum(int x){
	int sum = 0;
	for(int ix = x; ix != 0; ix -= LOWBIT(ix)){
		sum += c[ix];
	}
	return sum;
}
int main(){
	int N;
	scanf("%d", &N);
	stack<int> s;
	char command[11];
	int value, K;
	for (int ix = 0; ix != N; ix++) {
		scanf("%s", command);
		if (command[1] == 'o') {
			if (s.empty()) {
				printf("Invalid\n");
			}
			else {
				printf("%d\n", s.top());
				update(s.top(), -1);
				s.pop();
			}
		}
		else
			if (command[1] == 'e') {
				if (s.empty()) {
					printf("Invalid\n");
				}
				else {
					K = (s.size() + 1) / 2;
					int left = 1, right = MAX, mid;
					while(left < right){
						mid = (left + right) / 2;
						if (get_sum(mid) >= K) right = mid;
						else                   left  = mid + 1;
					}
					printf("%d\n", left);
				}
			}
			else {
				scanf("%d", &value);
				s.push(value);
				update(value, 1);
			}
	}
	system("pause");
	return 0;
}