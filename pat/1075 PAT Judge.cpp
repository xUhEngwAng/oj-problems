#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
class user{
public:
	vector<int> marks;
	int id;
	int count;
	int total;
	user(int K){
		marks.assign(K, -2);
		count = 0;
		total = 0;
	}
	void calc_total(){
		for(auto It = marks.cbegin();It != marks.cend(); It++){
			if (*It > 0) total += *It;
		}
	}
	bool judge(){
		for(auto It = marks.cbegin(); It != marks.cend(); It++){
			if (*It >= 0) return 1;
		}
		return 0;
	}
	void print(int rank){
		printf("%d %05d %d", rank, id, total);
		for(auto It = marks.cbegin(); It != marks.cend(); It++){
			if (*It >= 0) printf(" %d", *It);
			else if (*It == -1) printf(" 0");
			else if (*It == -2) printf(" -");
		}
		printf("\n");
	}
};
int main() {
	int M, N, K;
	scanf("%d %d %d", &N, &K, &M);
	vector<int> fullMark(K);
	vector<user> usersInfo(N, user(K));
	for (int ix = 0; ix != K; ix++)
		scanf("%d", &fullMark[ix]);
	int userId, probId, score;
	for (int ix = 0; ix != M; ix++) {
		scanf("%d %d %d", &userId, &probId, &score);
		usersInfo[userId - 1].id = userId;
		if (usersInfo[userId - 1].marks[probId - 1] < score) {
			usersInfo[userId - 1].marks[probId - 1] = score;
			if (score == fullMark[probId - 1]) usersInfo[userId - 1].count++;
		}
	}
	for_each(usersInfo.begin(), usersInfo.end(), [](user& usr) {usr.calc_total(); });
	stable_sort(usersInfo.begin(), usersInfo.end(), [](user usr1, user usr2) {return usr1.count > usr2.count; });
	stable_sort(usersInfo.begin(), usersInfo.end(), [](user usr1, user usr2) {return usr1.total > usr2.total; });
	int lastRank = 0, lastTotal = 0;
	for (int rank = 1; rank != usersInfo.size() + 1; rank++) {
		if (usersInfo[rank - 1].total == 0 && !usersInfo[rank - 1].judge()) break;
		if (usersInfo[rank - 1].total == lastTotal) usersInfo[rank - 1].print(lastRank);
		else {
			usersInfo[rank - 1].print(rank);
			lastRank = rank;
			lastTotal = usersInfo[rank - 1].total;
		}
	}
	system("pause");
	return 0;
}
