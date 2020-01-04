#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
using namespace std;

#define NEWVERSION

#ifdef NEWVERSION

#define POS(X)        (blocks_pos[X])
#define dest_tower    (towers[POS(dest)])
#define src_tower     (towers[POS(src)])

int main(){
	int n;
	cin >> n;
	cin.ignore();
	vector<int> blocks_pos(n);
	for(int ix = 0; ix != n; ++ix)
		blocks_pos[ix] = ix;
	vector<vector<int>> towers(n);
	for(int ix = 0; ix != n; ++ix)
		towers[ix].push_back(ix);

	string cmd, op1, op2;
	int src, dest, curr;
	stack<int> s;
	while(true){
		getline(cin, cmd);
		op1  = cmd.substr(0, 4);
		if(op1 == "quit") break;
		op2  = cmd.substr(7, 4);
		src  = cmd[5] - '0';
		dest = cmd[12] - '0';

		if(POS(src) == POS(dest)) continue;

		if(op2 == "onto"){
			while ((curr = dest_tower.back()) != dest) {
				POS(curr) = curr;
				towers[curr].push_back(curr);
				dest_tower.pop_back();
			}
		}

		if(op1 == "move"){
			while ((curr = src_tower.back()) != src) {
				POS(curr) = curr;
				towers[curr].push_back(curr);
				src_tower.pop_back();
			}
			dest_tower.push_back(src);
			src_tower.pop_back();
			POS(src) = POS(dest);
		}
		else{//op1 == "pile"
			while((curr = src_tower.back()) != src){
				s.push(curr);
				src_tower.pop_back();
				POS(curr) = POS(dest);
			}
			s.push(src);
			src_tower.pop_back();
			POS(src) = POS(dest);
			while(!s.empty()){
				dest_tower.push_back(s.top());
				s.pop();
			}
		}
	}
	for(int ix = 0; ix != n; ++ix){
		cout << endl;
		cout << ix << ':';
		for(int block : towers[ix])
			cout << ' ' << block;
	}
	cout << endl << endl;
	int count = 0;
	for(int pos : blocks_pos)
        cout << count++ << ": " << pos << endl;
	system("pause");
	return 0;
}

#else

class tower{
public:
	int pos;
	vector<int> blocks;
};

int main(){
	int n;
	cin >> n;
	cin.ignore();
	vector<tower> towers(n);
	for(int ix = 0; ix != n; ++ix){
		towers[ix].pos = ix;
		towers[ix].blocks.push_back(ix);
	}

	string cmd, op1, op2;
	int src, dest, src_tower(src), dest_tower(dest), num, curr;
	vector<int>::iterator src_block, dest_block;
	while(true){
		//parse command
		getline(cin, cmd);
		op1  = cmd.substr(0, 4);
		if(op1 == "quit") break;
		op2  = cmd.substr(7, 4);
		src  = cmd[5] - '0';
		dest = cmd[12] - '0';

		src_tower(src) = towers[src].pos;
		dest_tower(dest) = towers[dest].pos;
		if(src_tower(src) == dest_tower(dest)) continue;
		src_block  = find(towers[src_tower(src)].blocks.begin(), towers[src_tower(src)].blocks.end(), src);
		dest_block = find(towers[dest_tower(dest)].blocks.begin(), towers[dest_tower(dest)].blocks.end(), dest);

		if(op1 == "move"){
            num = towers[src_tower(src)].blocks.end() - src_block - 1;
			while(num--){
                curr = towers[src_tower(src)].blocks.back();
				towers[curr].blocks.push_back(curr);
				towers[curr].pos = curr;
                towers[src_tower(src)].blocks.pop_back();
			}
		}
		if(op2 == "onto"){
            num = towers[dest_tower(dest)].blocks.end() - dest_block - 1;
			while(num--){
			    curr = towers[dest_tower(dest)].blocks.back();
				towers[curr].blocks.push_back(curr);
				towers[curr].pos = curr;
				towers[dest_tower(dest)].blocks.pop_back();
			}
		}
		if(op1 == "move"){
            towers[dest_tower(dest)].blocks.push_back(src);
            towers[src].pos = dest_tower(dest);
            towers[src_tower(src)].blocks.pop_back();
		}
		else{
            for(auto it = src_block; it != towers[src_tower(src)].blocks.end(); ++it){
                towers[dest_tower(dest)].blocks.push_back(*it);
                towers[*it].pos = dest_tower(dest);
            }
            num = towers[src_tower(src)].blocks.end() - src_block;
            while(num--)
                towers[src_tower(src)].blocks.pop_back();
		}
	}

	cout << "0:";
	for(auto it = towers[0].blocks.begin(); it != towers[0].blocks.end(); ++it)
        cout << ' ' << *it;
	for(int ix = 1; ix != n; ++ix){
        cout << endl;
		cout << ix << ':';
		for(auto it = towers[ix].blocks.begin(); it != towers[ix].blocks.end(); ++it)
			cout << ' ' << *it;
	}
	return 0;
}
#endif
/*
10
move 1 over 0
move 3 onto 2
move 5 over 4
pile 7 onto 6
pile 9 over 8
pile 2 over 0
pile 6 onto 4
move 8 over 0
move 4 onto 0
quit
*/
