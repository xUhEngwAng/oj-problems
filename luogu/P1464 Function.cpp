#include <cstdio>
#include <cstring>

/*
 * 这样一个水题我都思考了好一会儿时间。一眼即可看出，这个题需要
 * 记忆化搜索，我思考的问题是，应该按照什么样的次序进行遍历，才
 * 能保证当前 w(a, b, c) 所依赖的项在此前就被计算出来了。
 *
 * 实际上，只要写一个三重循环，分别从小到大枚举 a, b, c 就可以
 * 了。这里需要注意一个问题，对于 a, b, c 中有一个为零时，要初
 * 始化为1，一开始我直接用 memset(w, 1, sizeof(w)) 来做，出现
 * 了意想不到的问题。这是因为 memset 是逐个比特进行设置的，这样
 * 设置后的结果乃是每一个元素都为 0x1111。
 */

int w[21][21][21];

void init(){
	for(int ix = 0; ix <= 20; ++ix)
        for(int jx = 0; jx <= 20; ++jx){
            w[0][ix][jx] = 1;
            w[ix][0][jx] = 1;
            w[ix][jx][0] = 1;
    }
	for(int ix = 1; ix <= 20; ++ix)
		for(int jx = 1; jx <= 20; ++jx)
			for(int kx = 1; kx <= 20; ++kx){
				if(ix < jx && jx < kx)
					w[ix][jx][kx] = w[ix][jx][kx-1] + w[ix][jx-1][kx-1] - w[ix][jx-1][kx];
				else
					w[ix][jx][kx] = w[ix-1][jx][kx] + w[ix-1][jx-1][kx] + w[ix-1][jx][kx-1]-w[ix-1][jx-1][kx-1];
                //printf("w(%d, %d, %d) = %d\n", ix, jx, kx, w[ix][jx][kx]);
			}
}

int main(){
	int a, b, c, res;
	init();
	while(scanf("%d %d %d", &a, &b, &c) == 3){
		if(a == -1 && b == -1 & c == -1) break;
		if(a <= 0 || b <= 0 || c <= 0) res = 1;
		else
		if(a > 20 || b > 20 || c > 20) res = w[20][20][20];
		else res = w[a][b][c];
		printf("w(%d, %d, %d) = %d\n", a, b, c, res);
	}
	return 0;
}
