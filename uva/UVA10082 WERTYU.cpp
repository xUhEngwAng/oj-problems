#include <cstdio>

char row1[] = "`1234567890-=";
char row2[] = "QWERTYUIOP[]\\";
char row3[] = "ASDFGHJKL;'";
char row4[] = "ZXCVBNM,./";

int main(){
	int map[128];
	for(int ix = 1; ix != 13; ++ix)
		map[row1[ix]] = row1[ix - 1];
	for(int ix = 1; ix != 13; ++ix)
		map[row2[ix]] = row2[ix - 1];
	for(int ix = 1; ix != 11; ++ix)
		map[row3[ix]] = row3[ix - 1];
	for(int ix = 1; ix != 10; ++ix)
		map[row4[ix]] = row4[ix - 1];
	char ch;
	while((ch = getchar()) != EOF){
		if(ch == ' ' || ch == '\n')
			putchar(ch);
		else
			putchar(map[ch]);
	}
	return 0;
}
