#include <stdio.h>
#include <vector>

using std::vector;

int main(int argc, char* argv[]){
	short stackCap, Num, K;
	scanf("%hd %hd %hd", &stackCap, &Num, &K);

	vector<short> sequence(Num);
	vector<short>::const_iterator seqIter, localIter;
	short lastMax, expect, fail, success, size;
	for (short ix = 0; ix != K; ix++) {
		success = 1;
		lastMax = 0;
		fail    = 0;
		size    = 0;
		//read in data
		for (short jx = 0; jx != Num; jx++)
			scanf("%hd", &sequence[jx]); 
		//main loop
		for (seqIter = sequence.begin(); seqIter != sequence.end(); seqIter++){
			if (*seqIter < lastMax) {
				size--;
				continue;
			}

			//else
			size = size + *seqIter - lastMax - 1;
			if(size + 1 > stackCap) {//stack overflow
				success = 0;
				break;
			}
			//else
			//check the order of pre-numbers
			expect = *seqIter - 1;
			for(localIter = seqIter+1; localIter != sequence.end(); localIter++){
				//if (expect == lastMax) break;//success

				if (*localIter < *seqIter && *localIter > lastMax) {
					if (*localIter != expect) {//unmatching
						fail = 1;
						break;
					}//else
					expect--;
				}
			}
			if(fail){
				success = 0;
				break;
			}
			lastMax = *seqIter;
		}
		if (success) printf("YES\n");
		else 		 printf("NO\n");
	}
	
	return 0;
}
