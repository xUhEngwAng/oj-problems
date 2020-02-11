#include <cstdio>
#include <algorithm>
using namespace std;

/*
 * 这个题乍一看很简单，然而我三次把题意理解错误......
 * 这里是需要好好思考一下这个 Eddington Number 的含义。
 */

int main(){
	int N, curr, count = 0;
	scanf("%d", &N);
	int *arr = new int[N];
	for(int ix = 0; ix != N; ++ix)
		scanf("%d", arr + ix);
	sort(arr, arr + N);
	for(int ix = N - 1, jx; ix >= 0; --ix){
	    curr = arr[ix];
        ++count;
        if(curr - 1 == count)
            break;
        if(curr - 1 < count){
            count -= 1;
            break;
        }
	}
	printf("%d\n", count);
	return 0;
}
