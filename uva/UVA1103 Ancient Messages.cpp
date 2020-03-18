#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * 此题乍一看下相当离谱，图片识别问题？这是想要我手写一个
 * 卷积神经网络？？？思考了许久未果，看了看各路大神的解答，
 * 才终于找到思路。
 *
 * 首先考虑整张图片只有一个图形（连通分量）的情况。为了将
 * 六张图形区别开，需要提取出各自具有的特征，这里的特征即
 * 图片中的白洞的数量，后者等于图中白色像素组成的连通分量
 * 的个数，这样一次 dfs 就可以解决问题了。
 *
 * 而如果一张图片中含有多个图形，上述的方法就不能工作了。
 * 为了解决这个问题，可以把每个图形分别拷贝到一个空白的
 * 背景上，这需要对黑色像素做一次 dfs，此后问题就转化为
 * 了上面的情形。
 *
 * 然而此时我的代码仍然是 Wrong Answer......看了大佬的
 * 的博客后，才发现问题。考虑一种情况，黑色像素延伸到了图
 * 片的边框，这样图片的白色背景被分为了好几块，因此会得到
 * 多个白色连通分量。为了解决这个问题，只需要给图片加上一个
 * 白色边框，就可以将背景全部连接起来了。
 */

int H, W;
bool graph[202][202], copied[202][202];
bool visited[202][202], copy_visited[202][202];

void print(bool (*graph)[202]){
	for(int ix = 0; ix <= H + 1; ++ix){
		for(int jx = 0; jx <= W * 4 + 1; ++jx)
			if(graph[ix][jx]) printf("1");
			else printf("0");
		printf("\n");
	}
}

bool isdigit(char ch){
    if(ch >= '0' && ch <= '9') return true;
    return false;
}

void copy_graph(int row, int col){
	visited[row][col] = true;
	copied[row][col] = 0;
	if(graph[row - 1][col] && !visited[row - 1][col])
		copy_graph(row - 1, col);
	if(graph[row][col - 1] && !visited[row][col - 1])
		copy_graph(row, col - 1);
	if(graph[row + 1][col] && !visited[row + 1][col])
		copy_graph(row + 1, col);
	if(graph[row][col + 1] && !visited[row][col + 1])
		copy_graph(row, col + 1);
}

void dfs(int row, int col){
	copy_visited[row][col] = true;
	if(copied[row - 1][col] && !copy_visited[row - 1][col])
		dfs(row - 1, col);
	if(copied[row][col - 1] && !copy_visited[row][col - 1])
		dfs(row, col - 1);
	if(copied[row + 1][col] && !copy_visited[row + 1][col])
		dfs(row + 1, col);
	if(copied[row][col + 1] && !copy_visited[row][col + 1])
		dfs(row, col + 1);
}

int countCircle(){
	memset(copy_visited, 0, sizeof(copy_visited));
	int res = 0;
	for(int ix = 0; ix <= H + 1; ++ix)
		for(int jx = 0; jx <= 4 * W + 1; ++jx){
			if(copied[ix][jx] && !copy_visited[ix][jx]){
				dfs(ix, jx);
				++res;
			}
		}
	return res;
}

int main(){
    //freopen("1.out", "w", stdout);
	int curr, cnt = 1, pos, num;
	char ch;
	vector<char> res;
	while(true){
		scanf("%d %d", &H, &W);
		if(H == 0) break;
		printf("Case %d: ", cnt++);
		memset(graph, 0, sizeof(graph));
        memset(visited, 0, sizeof(visited));
        res.clear();
        for(int ix = 1; ix <= H; ++ix){
        	getchar();
        	for(int jx = 1; jx <= W; ++jx){
        		scanf("%c", &ch);
        		if(isdigit(ch)) curr = ch - '0';
        		else curr = ch - 'a' + 10;
        		pos = 4 * jx - 1;
        		while(curr){
        			if(curr & 1) graph[ix][pos] = true;
        			curr = curr >> 1;
        			--pos;
        		}
        	}
        }
        //print(graph);
        //printf("\n");
        for(int ix = 1; ix <= H; ++ix)
            for(int jx = 1; jx <= W * 4; ++jx){
            if(graph[ix][jx] && !visited[ix][jx]){
            	memset(copied,  1, sizeof(copied));
                copy_graph(ix, jx);
                //print(copied);
                //printf("\n");
                num = countCircle();
                if(num == 1) res.push_back('W');
                else if(num == 2) res.push_back('A');
                else if(num == 3) res.push_back('K');
                else if(num == 4) res.push_back('J');
                else if(num == 5) res.push_back('S');
                else res.push_back('D');
            }
        }
       	sort(res.begin(), res.end());
       	for(int ix = 0; ix != res.size(); ++ix)
       		printf("%c", res[ix]);
       	printf("\n");
	}
	return 0;
}
