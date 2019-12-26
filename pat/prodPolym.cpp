#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;
struct poly {
	int N;
	float an;
};
int main() {
	int K1, K2;
	cin >> K1;
	vector<poly> ply1(K1);
	for (auto plyIter = ply1.begin(); plyIter != ply1.end(); plyIter++)
		cin >> plyIter->N >> plyIter->an;
	cin >> K2;
	vector<poly> ply2(K2);
	for (auto plyIter = ply2.begin(); plyIter != ply2.end(); plyIter++)
		cin >> plyIter->N >> plyIter->an;
	vector<poly> result;
	poly tmp;
	for (auto plyIter1 = ply1.begin(); plyIter1 != ply1.end(); plyIter1++) {
		for (auto plyIter2 = ply2.begin(); plyIter2 != ply2.end(); plyIter2++) {
			tmp.N = plyIter1->N + plyIter2->N;
			tmp.an = plyIter1->an * plyIter2->an;
			result.push_back(tmp);
		}
	}
	vector<poly>::iterator maxPos;
	for (auto plyIter = result.begin(); plyIter != result.end() - 1; plyIter++) { // sort result according to N
		maxPos = plyIter;
		for (auto localIter = plyIter + 1; localIter != result.end(); localIter++) {
			if (localIter->N > maxPos->N) maxPos = localIter;
		}
		tmp = *plyIter;
		*plyIter = *maxPos;
		*maxPos = tmp;
	}
	vector<poly> mergeResult;
	for (auto plyIter = result.begin(); plyIter != result.end();) {
		tmp = *plyIter;
		while (++plyIter != result.end() && plyIter->N == tmp.N)
			tmp.an += plyIter->an;
		if(tmp.an != 0) mergeResult.push_back(tmp);
	}
	cout << mergeResult.size();
	for (auto plyIter = mergeResult.begin(); plyIter != mergeResult.end(); plyIter++)
		printf(" %d %.1f", plyIter->N, plyIter->an);
	system("pause");
	return 0;
}
