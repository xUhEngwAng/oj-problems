#include <cstdio>
#include <vector>
using namespace std;

/*
 * 这就是一个简单模拟题，也不知道我当初为什么做了好久都是
 * RE。整体思路的话就搞个 vector<vector<int>> 来模拟这里
 * 的一堆方块，利用一个向量来记录每一个块所在的位置。
 *
 * 此后就是分别实现四个操作就可以了，我这里是分别写了四个
 * 函数，虽然代码长了点，但是结构非常规整，所有四个操作
 * 也有共通之处，完成一个函数另外三个就可以迅速完成了。
 * 相较之下，我当初是都写在 main 里面的，非常纠结，debug
 * 起来想必是有一些困难。
 *
 * 这里四个函数的实现也有大量的冗余，比如将某个块上的其他
 * 块清空可以另写一个函数 clear_above，这样代码可以更加
 * 简练。
 */

vector<vector<int>> tower;
vector<int> pos;

void move_onto(int one, int two){
	int pos1 = pos[one], pos2 = pos[two];
	if(pos1 == pos2) return;
	int curr;
	while(tower[pos1].back() != one){
		curr = tower[pos1].back();
		tower[curr].push_back(curr);
		pos[curr] = curr;
		tower[pos1].pop_back();
	}
	while(tower[pos2].back() != two){
		curr = tower[pos2].back();
		tower[curr].push_back(curr);
		pos[curr] = curr;
		tower[pos2].pop_back();
	}
	tower[pos2].push_back(one);
	pos[one] = pos2;
	tower[pos1].pop_back();
}

void move_over(int one, int two){
	int pos1 = pos[one], pos2 = pos[two];
	if(pos1 == pos2) return;
	int curr;
	while(tower[pos1].back() != one){
		curr = tower[pos1].back();
		tower[curr].push_back(curr);
		pos[curr] = curr;
		tower[pos1].pop_back();
	}
	tower[pos2].push_back(one);
	pos[one] = pos2;
	tower[pos1].pop_back();
}

void pile_onto(int one, int two){
	int pos1 = pos[one], pos2 = pos[two];
	if(pos1 == pos2) return;
	int curr;
	while(tower[pos2].back() != two){
		curr = tower[pos2].back();
		tower[curr].push_back(curr);
		pos[curr] = curr;
		tower[pos2].pop_back();
	}
	curr = 0;
	while(tower[pos1][curr] != one) ++curr;
	for(int ix = curr; ix != tower[pos1].size(); ++ix){
		tower[pos2].push_back(tower[pos1][ix]);
		pos[tower[pos1][ix]] = pos2;
	}
	tower[pos1].resize(curr);
}

void pile_over(int one, int two){
	int pos1 = pos[one], pos2 = pos[two];
	if(pos1 == pos2) return;
	int curr = 0;
	while(tower[pos1][curr] != one) ++curr;
	for(int ix = curr; ix != tower[pos1].size(); ++ix){
		tower[pos2].push_back(tower[pos1][ix]);
		pos[tower[pos1][ix]] = pos2;
	}
	tower[pos1].resize(curr);

}

int main(){
	int n, one, two;
	scanf("%d", &n);
	tower.resize(n);
	for(int ix = 0; ix != n; ++ix){
		pos.push_back(ix);
		tower[ix].push_back(ix);
	}
	char cmd1[4], cmd2[4];
	while(true){
		scanf("%s", cmd1);
		if(cmd1[0] == 'q') break;
		scanf("%d %s %d", &one, cmd2, &two);
		if(cmd1[0] == 'm')
			if(cmd2[1] == 'n') move_onto(one, two);
			else               move_over(one, two);
		else
			if(cmd2[1] == 'n') pile_onto(one, two);
			else               pile_over(one, two);
	}
	for(int ix = 0; ix != n; ++ix){
		printf("%d:", ix);
		for(int e : tower[ix])
			printf(" %d", e);
		printf("\n");
	}
	return 0;
}
