#include <string>
#include <iostream>
using namespace std;

/*
 * 这个题固然是非常简单，但是我也学会了一些东西。比如使用
 * getchar 来逐个读取字符，有可能会比整个读取一行处理起来
 * 更加方便。然后如果文件结束，getchar 将返回 EOF，需要对
 * 其进行判断来结束输入。 
 */

int main(){
	int count = 0;
	string curline;
	char ch;
	while((ch = getchar()) != EOF){
		if(ch == '"'){
			++count;
			if(count & 1)
				printf("``");
			else
				printf("''");
		}
		else putchar(ch);
	}
	return 0;
}
