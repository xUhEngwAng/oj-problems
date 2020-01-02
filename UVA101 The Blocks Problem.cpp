#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

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
	int src, dest, src_tower, dest_tower, num, curr;
	vector<int>::iterator src_block, dest_block;
	while(true){
		//parse command
		getline(cin, cmd);
		op1  = cmd.substr(0, 4);
		if(op1 == "quit") break;
		op2  = cmd.substr(7, 4);
		src  = cmd[5] - '0';
		dest = cmd[12] - '0';

		src_tower = towers[src].pos;
		dest_tower = towers[dest].pos;
		if(src_tower == dest_tower) continue;
		src_block  = find(towers[src_tower].blocks.begin(), towers[src_tower].blocks.end(), src);
		dest_block = find(towers[dest_tower].blocks.begin(), towers[dest_tower].blocks.end(), dest);

		if(op1 == "move"){
            num = towers[src_tower].blocks.end() - src_block - 1;
			while(num--){
                curr = towers[src_tower].blocks.back();
				towers[curr].blocks.push_back(curr);
				towers[curr].pos = curr;
                towers[src_tower].blocks.pop_back();
			}
		}
		if(op2 == "onto"){
            num = towers[dest_tower].blocks.end() - dest_block - 1;
			while(num--){
			    curr = towers[dest_tower].blocks.back();
				towers[curr].blocks.push_back(curr);
				towers[curr].pos = curr;
				towers[dest_tower].blocks.pop_back();
			}
		}
		if(op1 == "move"){
            towers[dest_tower].blocks.push_back(src);
            towers[src].pos = dest_tower;
            towers[src_tower].blocks.pop_back();
		}
		else{
            for(auto it = src_block; it != towers[src_tower].blocks.end(); ++it){
                towers[dest_tower].blocks.push_back(*it);
                towers[*it].pos = dest_tower;
            }
            num = towers[src_tower].blocks.end() - src_block;
            while(num--)
                towers[src_tower].blocks.pop_back();
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
