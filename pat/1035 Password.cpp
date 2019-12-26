#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 11

int main() {
	short int N;//total number of accounts
	scanf("%hd", &N);

	char(*userName)[LEN], (*password)[LEN];
	userName = (char(*)[LEN])malloc(sizeof(char[LEN])*N);
	password = (char(*)[LEN])malloc(sizeof(char[LEN])*N);

	
	for (short int ix = 0; ix < N; ix++) {
		scanf("%s %s", userName[ix], password[ix]);
	}
	
	short int count = 0, flag;// count modified accounts
	char currPw[LEN];
	//main loop
	for (short int ix = 0; ix < N; ix++) {
		strcpy(currPw, password[ix]);
		flag = 0;//indicating modified

		//search current password
		for (short int jx = 0; currPw[jx] != '\0'; jx++) {
			switch (currPw[jx]) {
			case '1':
				currPw[jx] = '@';
				flag = 1;
				break;

			case '0':
				currPw[jx] = '%';
				flag = 1;
				break;

			case 'l':
				currPw[jx] = 'L';
				flag = 1;
				break;

			case 'O':
				currPw[jx] = 'o';
				flag = 1;
				break;

			default:
				break;
			}
		}
		if (flag) {
			strcpy(password[count], currPw);
			strcpy(userName[count], userName[ix]);
			count++;
		}

	}
	
	//print result
	if (count == 0) {
		if (N == 1) printf("There is 1 account and no account is modified");
		else printf("There are %hd accounts and no account is modified", N);
	}
	
	else {
		printf("%hd\n", count);
		char currName[LEN];
		
		for (short int ix = 0; ix < count; ix++) {
			strcpy(currName, userName[ix]);
			strcpy(currPw, password[ix]);
			printf("%s %s\n", userName[ix], password[ix]);
		}
	}
	


	return 0;
}
