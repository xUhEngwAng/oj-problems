#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct player{
	string name;
	int score[4];
	int total = 0;
	int round_finished = 0;
};

float percent[70];
vector<player> table;

bool cmp1(const player &one, const player &two){
	return one.score[0] + one.score[1] < two.score[0] + two.score[1];
}

bool cmp2(const player &one, const player &two){
	if(one.round_finished != two.round_finished)
		return one.round_finished > two.round_finished;
	if(one.total != two.total)
		return one.total < two.total;
	return one.name < two.name;
}

void parse(const string &line){
	player tmp;
	string name = line.substr(0, 20);
	while(name.back() == ' ') name.pop_back();
	tmp.name = name;
	string score;
	for(int ix = 21, cnt = 0; ix <= 30; ix += 3, cnt++){
		score = line.substr(ix, 3);
		if(score[0] == 'D') break;
		tmp.score[cnt] = stoi(score);
		tmp.round_finished++;
		tmp.total += tmp.score[cnt];
	}
	if(tmp.round_finished >= 2)
		table.push_back(tmp);
}

void printHeader(){
	cout << "Player Name          Place     RD1  RD2  RD3  RD4  TOTAL     Money Won" << endl;
	cout << "-----------------------------------------------------------------------" << endl;
}

int main(){
	freopen("1.out", "w", stdout);
	int t, num, score, ix, jx;
	float total_prize, prize_ratio;
	float curr_prize;
	int prize_rank, tie_cnt;
	string line, rank;
	cin >> t;
	while(t--){
		cin >> total_prize;
		for(int ix = 0; ix != 70; ++ix)
			cin >> percent[ix];
		cin >> num;
		cin.ignore();
		table.clear();
		for(int ix = 0; ix != num; ++ix){
			getline(cin, line);
			parse(line);
		}
		sort(table.begin(), table.end(), cmp1);
		if(table.size() >= 70){
			score = table[69].score[0] + table[69].score[1];
			for(num = 70; num < table.size(); ++num)
				if(table[num].score[0] + table[num].score[1] > score)
					break;
			table.resize(num);
		}
		sort(table.begin(), table.end(), cmp2);
		prize_rank = 0;
		num = table.size();
		while(table[num - 1].round_finished != 4) --num;
		printHeader();
		for(ix = 0; ix != num; ){
			tie_cnt = 0;
			prize_ratio = 0;
			for(jx = ix; jx != num; ++jx){
				if(table[jx].total > table[ix].total) break;
				if(table[jx].name.back() != '*'){
					++tie_cnt;
					if(prize_rank < 70)
						prize_ratio += percent[prize_rank++];
				}
			}
			if(tie_cnt != 0)
				curr_prize = total_prize * prize_ratio / (tie_cnt * 100);
			for(int kx = ix; kx != jx; ++kx){
				cout << std::left << setw(21) << table[kx].name;
				rank = to_string(ix + 1);
				if(table[kx].name.back() != '*' && tie_cnt >= 2) 
					rank.push_back('T');
				cout << setw(10) << rank;
				for(int i = 0; i != 4; ++i)
					cout << std::left << setw(5) << table[kx].score[i];
				cout << std::left << setw(10) << table[kx].total;
				if(table[kx].name.back() != '*'){
					cout << '$';
					cout << std::right << setw(9) << fixed << setprecision(2) << curr_prize;
				}
				cout << endl;
			}
			ix = jx;
		}
		for(ix = num; ix != table.size(); ++ix){
			cout << std::left << setw(21) << table[ix].name;
			cout << setw(10) << ' ';
			for(int i = 0; i != table[ix].round_finished; ++i)
				cout << std::left << setw(5) << table[ix].score[i];
			for(int i = table[ix].round_finished; i != 4; ++i)
				cout << setw(5) << ' ';
			cout << "DQ" << endl;
		}
		if(t != 0) cout << endl;
	}
	return 0;
}
