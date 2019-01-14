#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#define  MAXRADIX 100
#define  MAX(X,Y) ((X)>(Y)?(X):(Y))
using namespace std;
short findMax(string src) {
	string::iterator strIter;
	short max = 0, currBit;
	for (strIter = src.begin(); strIter != src.end(); strIter++) {
		if (*strIter >= '0' && *strIter <= '9') currBit = *strIter - '0';
		else if (*strIter >= 'a' && *strIter <= 'z') currBit = *strIter - 'a' + 10;
		else return -1;
		if (currBit > max) max = currBit;
	}
	return max;
}
long long countDecimal(string src, short radix) {
	string::iterator strIter;
	string::size_type currIx = src.size() - 1, currBit;
	long long result = 0;
	for (strIter = src.begin(); strIter != src.end(); strIter++) {
		if (*strIter >= '0' && *strIter <= '9') currBit = *strIter - '0';
		else if (*strIter >= 'a' && *strIter <= 'z') currBit = *strIter - 'a' + 10;
		else return -1;
		result += currBit * pow(radix, currIx);
		currIx--;
	}
	return result;
}
int main() {
	string strN1, strN2;
	short tag, radix, ix;
	long long  decimalN1, decimalN2; // 35^10 > 2^32
	cin >> strN1 >> strN2 >> tag >> radix;

	switch (tag) {
	case 1:
		decimalN1 = countDecimal(strN1, radix);
		for (ix = MAX(2,findMax(strN2) + 1); ix <= MAXRADIX; ix++) {
			decimalN2 = countDecimal(strN2, ix);
			if (decimalN1 == decimalN2) {
				cout << ix << endl;
				break;
			}
		}
		if (ix == MAXRADIX + 1) cout << "Impossible" << endl;
		break;
	case 2:
		decimalN2 = countDecimal(strN2, radix);
		for (ix = MAX(2,findMax(strN1) + 1); ix <= MAXRADIX; ix++) {
			decimalN1 = countDecimal(strN1, ix);
			if (decimalN1 == decimalN2) {
				cout << ix << endl;
				break;
			}
		}
		if (ix == MAXRADIX + 1) cout << "Impossible" << endl;
		break;
		//default:
	}
	system("pause");
	return 0;
}
