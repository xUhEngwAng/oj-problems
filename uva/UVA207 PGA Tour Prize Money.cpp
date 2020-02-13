#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

void printHeader();
void printInfo(int num);
void computePrize(int num);
int  parseEntry(string entry, int pos);

bool cutCmp(const Player& one, const Player& two){
	return one.cutScore > two.cutScore;
}

bool prizeCmp(const Player& one, const Player& two){
	if(one.roundComplete != two.roundComplete)
		return one.roundComplete > two.roundComplete;
	if(one.total != two.total)
		return one.total > two.total;
	return one.name < two.name;
}

enum Status{AMATEUR, PROFESSION};

struct Player{
	string name, rank;
	Status status;
	int roundComplete;
	int rd1, rd2, rd3, rd4, total, cutScore;
	bool hasPrize;
	float prize;
};

float percentage[70], purse;
Player players[144];

int main(){
	int cases, nplayers, pos, cutNum;
	string entry;
	cin >> cases;
	cin.ignore();
	while(cases--){
		getline(cin, entry);
		cin >> purse;
		for(int ix = 0; ix != 70; ++ix)
			cin >> percentage[ix];
		cin >> nplayers;
		pos = 0;
		for(int ix = 0; ix != nplayers; ++ix){
			getline(cin, entry);
			pos = parseEntry(entry, pos);
		}

		sort(players, players + pos, cutCmp);
		cutNum = 70;
		while(cutNum < pos && players[cutNum]==players[cutNum - 1])
			++cutNum;

		sort(players, players + cutNum, prizeCmp);
		computePrize(cutNum);
		printInfo(cutNum);
	}
	return 0;
}

void printInfo(int num){
	printHeader();
	Player curr;

	for(int ix = 0; ix != num; ++ix){
		curr = players[ix];
		cout << curr.name;

	}
}

void computePrize(int num){
	int prevTotal = 0, jx, rank, prizeRank = 0, prevCount
	float percent;
	for(int ix = 0; ix < num && prizeRank < 70; ){
		prevTotal = players[ix].total;
		percent   = 0;
		prizeCount = 0;
		for(jx = ix; jx < num; ++jx){
			if(players[jx].total != prevTotal)
				break;
			if(players[jx].status != AMATEUR){
				percent += percentage[prizeRank++];
				prizeCount++;
			}
		}
		rank = ix + 1;
		if(prizeCount != 0) 
			percent = percent / prizeCount;
		while(ix < jx){
			players[ix].rank = to_string(rank);
			if(players[ix].status == AMATEUR){
				players[ix].hasPrize = false;
			}else{
				if(prizeCount > 1) 
					players[ix].rank.push_back('T');
				players[ix].prize = purse * percent;
				players[ix].hasPrize = true;
			}
			++ix;
		}
	}
}
