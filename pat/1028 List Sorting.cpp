#include <vector>
#include <string>
#include <iostream>
using namespace std;
struct stu {
	string stuid;
	string stuname;
	int    score;
};
int main() {
	int N, mode;
	scanf("%d %d", &N, &mode);
	vector<stu> stuVec(N);
	for (auto stuIt = stuVec.begin(); stuIt != stuVec.end(); stuIt++) {
		cin >> stuIt->stuid >> stuIt->stuname >> stuIt->score;
	}
	vector<stu>::iterator maxpos;
	stu tmp;
	switch (mode) {
	case 1: // selective sort by stuid
		for (auto stuIt = stuVec.begin(); stuIt != stuVec.end() - 1; stuIt++) {
			maxpos = stuIt;
			for (auto localIt = stuIt + 1; localIt != stuVec.end(); localIt++)
				if (localIt->stuid < maxpos->stuid) maxpos = localIt;
			tmp = *stuIt;
			*stuIt = *maxpos;
			*maxpos = tmp;
		}
		break;
	case 2:
		for (auto stuIt = stuVec.begin(); stuIt != stuVec.end() - 1; stuIt++) {
			maxpos = stuIt;
			for (auto localIt = stuIt + 1; localIt != stuVec.end(); localIt++)
				if (localIt->stuname < maxpos->stuname) maxpos = localIt;
			tmp = *stuIt;
			*stuIt = *maxpos;
			*maxpos = tmp;
		}
		break;
	case 3:
		for (auto stuIt = stuVec.begin(); stuIt != stuVec.end() - 1; stuIt++) {
			maxpos = stuIt;
			for (auto localIt = stuIt + 1; localIt != stuVec.end(); localIt++)
				if (localIt->score < maxpos->score) maxpos = localIt;
			tmp = *stuIt;
			*stuIt = *maxpos;
			*maxpos = tmp;
		}
		break;
	}
	for (auto stuIt = stuVec.begin(); stuIt != stuVec.end(); stuIt++) {
		//printf("%s %s %d\n", stuIt->stuid, stuIt->stuname, stuIt->score);
		cout << stuIt->stuid << ' '<< stuIt->stuname << ' ' << stuIt->score << endl;
	}

	system("pause");
	return 0;
}
