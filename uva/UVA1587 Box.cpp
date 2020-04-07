#define VERSION2

/*
 * 此题乍看起来非常简单，不就六个长方形吗，我就是逐个枚举都做完
 * 了，然而我一开始就是不会做，后来好不容易才想出来一个很愚蠢的
 * 算法。
 *
 * 这个算法的基本思想就是模拟拼接的过程，我将长方体的前面、左边、
 * 上边分别编号为 0, 1, 2，它们的对面为 5 - ix。然后逐个枚举每
 * 一个长方形，将它们依次放在各个位置尝试，整个过程是用试探回溯
 * 法做的。
 *
 * 这里的关键在于如何判断某个长方形是否可以放在某个位置，简单说
 * 来，首先判断它和对面的长方形是否相同（如果存在的话），如果不
 * 存在对面，则依次与和它相邻的两个面进行比对。
 *
 * 后来看了别人的算法，比我的简单太多。设长方体的长宽高分别是
 * a, b, c (c <= b <= a)，则六个长方形应分别是 ab, ab, ac, ac,
 * bc, bc。将读入的数据按照上面的次序排序，然后进行该判断即可。
 * 相对于我原来的100行，这个算法只需要40行即可。
 *
 * 总结一下我存在的问题，其实一开始我也想过类似的策略，比如六个
 * 长方形两两相同，至多存在三种不同的边长，这种。但是这些条件都
 * 是必要条件，是无法编码的。真正需要的，是像上面策略的充分条件。
 */

#ifdef VERSION1

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct pallet{
	int width = 0;
	int height = 0;
};

pallet box[6], raw[6];
bool visited[6];

bool isvalid(int curr_pos, int cnt){
	if(raw[cnt].width < raw[cnt].height)
		swap(raw[cnt].width, raw[cnt].height);
	int tmp = curr_pos;
	if(tmp == 3 && !visited[2]) return false;
	if(tmp == 4 && !visited[1]) return false;
	if(tmp >= 3) tmp = 5 - tmp;
	if(tmp == 0){
		if(raw[cnt].width == box[0].width && raw[cnt].height == box[0].height)
			return true;
		return false;
	}
	if(tmp == 1){
		if(visited[1]){
			if(box[1].width < box[1].height)
				swap(raw[cnt].width, raw[cnt].height);
			if(raw[cnt].width == box[1].width && raw[cnt].height == box[1].height)
				return true;
			return false;
		}
		if(!visited[2]){
			if(raw[cnt].height == box[0].height)
				return true;
			swap(raw[cnt].width, raw[cnt].height);
			if(raw[cnt].height == box[0].height)
				return true;
			return false;
		}
		if(box[0].height > box[2].height)
			swap(raw[cnt].width, raw[cnt].height);
		if(raw[cnt].width == box[2].height && raw[cnt].height == box[0].height)
			return true;
		return false;
	}

	if(tmp == 2){
		if(visited[2]){
			if(box[2].width < box[2].height)
				swap(raw[cnt].width, raw[cnt].height);
			if(raw[cnt].width == box[2].width && raw[cnt].height == box[2].height)
				return true;
			return false;
		}
		if(!visited[1]){
			if(raw[cnt].width == box[0].width)
				return true;
			swap(raw[cnt].width, raw[cnt].height);
			if(raw[cnt].width == box[0].width)
				return true;
			return false;
		}
		if(box[0].width < box[1].width)
			swap(raw[cnt].width, raw[cnt].height);
		if(raw[cnt].width == box[0].width && raw[cnt].height == box[1].width)
			return true;
		return false;
	}
}

bool dfs(int curr_pos, int cnt){
	visited[curr_pos] = true;
	box[curr_pos].width = raw[cnt].width;
	box[curr_pos].height = raw[cnt].height;
	//printf("%d\n", curr_pos);
	//printf("%d %d\n", raw[cnt].width, raw[cnt].height);

	if(cnt == 5) return true;
	for(int ix = 1; ix <= 5; ++ix)
		if(!visited[ix] && isvalid(ix, cnt + 1)){
			//printf("ix = %d\n", ix);
			if(dfs(ix, cnt + 1)) 
				return true;
		}

	visited[curr_pos] = false;
	box[curr_pos].width = 0;
	box[curr_pos].height = 0;
	return false;
}

int main(){
	freopen("1.out", "w", stdout);
	int curr_width, curr_height, cnt;
	bool res;
	while(scanf("%d %d", &curr_width, &curr_height) == 2){
		memset(box, 0, sizeof(box));
		memset(visited, 0, sizeof(visited));
		if(curr_width < curr_height)
			swap(curr_width, curr_height);
		raw[0].width  = curr_width;
		raw[0].height = curr_height;
		for(int ix = 1; ix <= 5; ++ix){
			scanf("%d %d", &curr_width, &curr_height);
			raw[ix].width = curr_width;
			raw[ix].height = curr_height;
		}
		res = dfs(0, 0);
		if(!res) printf("IMPOSSIBLE\n");
		else     printf("POSSIBLE\n");
	}
	return 0;
}

//VERSION 2
#else

#include <cstdio>
#include <algorithm>
using namespace std;

bool cmp(pair<int, int> one, pair<int, int> two){
	if(one.first == two.first)
		return one.second > two.second;
	return one.first > two.first;
}

int main(){
	//freopen("1.out", "w", stdout);
	pair<int, int> raw[6];
	int width, height;
	while(scanf("%d %d", &width, &height) == 2){
		if(width < height) swap(width, height);
		raw[0].first = width;
		raw[0].second = height;
		for(int ix = 1; ix != 6; ++ix){
			scanf("%d %d", &width, &height);
			if(width < height) swap(width, height);
			raw[ix].first = width;
			raw[ix].second = height;
		}
		sort(raw, raw + 6, cmp);
		if(!(raw[0] == raw[1])){
			printf("IMPOSSIBLE\n");
			continue;
		}
		if(!(raw[2] == raw[3] && raw[2].first == raw[0].first)){
			printf("IMPOSSIBLE\n");
			continue;
		}
		if(!(raw[4] == raw[5] && raw[4].first == raw[0].second && raw[4].second == raw[2].second)){
			printf("IMPOSSIBLE\n");
			continue;
		}
		printf("POSSIBLE\n");
	}
	return 0;
}

#endif
