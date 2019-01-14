#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int main(){
	int nonzeroNum1, exp1[MAX];
	float coeffc1[MAX];
	int nonzeroNum2, exp2[MAX];
	float coeffc2[MAX];

	scanf("%d", &nonzeroNum1);
	int ix = 0;
	while(getchar()!='\n'){
		scanf("%d %f", &exp1[ix], &coeffc1[ix]);
		ix++;
	}
	scanf("%d", &nonzeroNum2);
	int jx = 0;
	while (getchar() != '\n') {
		scanf("%d %f", &exp2[jx], &coeffc2[jx]);
		jx++;
	}
	//standardize original data: remove invalid(zero) data && same exponents
	for(int index  = 0; index < nonzeroNum1-1; index++){
		if(exp1[index] == exp1[index+1]){//merge
			coeffc1[index] += coeffc1[index + 1];
			for (int j = index + 1; j < nonzeroNum1 - 1; j++) {
				coeffc1[j] = coeffc1[j + 1];
				exp1[j] = exp1[j + 1];
			}
			nonzeroNum1--;
			index--;
		}
	}
	for (int index = 0; index < nonzeroNum2 - 1; index++) {
		if (exp2[index] == exp2[index + 1]) {//merge
			coeffc2[index] += coeffc2[index + 1];
			for (int j = index + 1; j < nonzeroNum2 - 1; j++) {
				coeffc2[j] = coeffc2[j + 1];
				exp2[j] = exp2[j + 1];
			}
			nonzeroNum2--;
			index--;
		}
	}

	int resultNum = 0, resultExp[2*MAX];
	float resultCoeffc[2*MAX];	
	int resultix = 0;

	for(ix = 0, jx = 0; ix < nonzeroNum1 && jx < nonzeroNum2;){
		if(exp1[ix] == exp2[jx]){
			resultExp[resultix] = exp1[ix];
			resultCoeffc[resultix] = coeffc1[ix] + coeffc2[jx];
			ix++, jx++, resultix++, resultNum++;
		}
		else
		if(exp1[ix] > exp2[jx]){
			resultExp[resultix]    = exp1[ix];
			resultCoeffc[resultix] = coeffc1[ix];
			ix++, resultix++, resultNum++;
		}
		else {//exp1[ix] < exp2[jx]
			resultExp[resultix] = exp2[jx];
			resultCoeffc[resultix] = coeffc2[jx];
			jx++, resultix++, resultNum++;
		}
	}
	while(ix != nonzeroNum1){
		resultExp[resultix] = exp1[ix];
		resultCoeffc[resultix] = coeffc1[ix];
		resultix++, ix++, resultNum++;
	}
	while (jx != nonzeroNum2) {
		resultExp[resultix] = exp2[jx];
		resultCoeffc[resultix] = coeffc2[jx];
		resultix++, jx++, resultNum++;
	}
	
	//remove zero data
	for(int index = 0; index < resultNum; index++){
		if(resultCoeffc[index] == 0){
			for (int j = index; j < resultNum - 1; j++){
				resultExp[j] = resultExp[j + 1];
				resultCoeffc[j] = resultCoeffc[j + 1];
			}
			resultNum--;
		}
	}

	//format output
	printf("%d", resultNum);
	for(int index = 0;index < resultNum; index ++){
		printf(" %d %.1f", resultExp[index], resultCoeffc[index]);
	}
	
	return 0;
}
