#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * 这个题我就直接暴力解了，反正我是觉得挺暴力的，后来看了看
 * 紫书的题解思路比我复杂多了，时间性能感觉也是我的比较好。
 *
 * 我的基本策略就是，对于每一个房屋，遍历所有其他房屋，将遮住
 * 的部分存储起来，这里是存储遮住部分的起始和终止位置。随后按
 * 起始位置进行排序，遍历所有这些区段，可以得到最长连续的遮挡
 * 部分，如果该区段完全包含了当前房屋，则说明完全被遮住了。
 * 编码起来我觉得也是容易一些。
 *
 * 然后参考题解上的离散化，其实是和我相反的思想。我是判断是否
 * 完全遮住了，参考题解是判断是否存在一部分漏了出来，大约就是
 * 直男和绅士之间的区别吧。
 */

struct building{
	float xpos, ypos;
	float width, height;
};

struct Line{
	float left, right;
	Line() = default;
	Line(float lpos, float rpos): left(lpos), right(rpos){}
	bool operator<(const Line &two){
		return left < two.left;
	}
};

vector<building> data;
vector<int> res;
vector<Line> intersection;

bool cmp(int one, int two){
	if(data[one].xpos == data[two].xpos)
		return data[one].ypos < data[two].ypos;
	return data[one].xpos < data[two].xpos;
}

int main(){
	int n, left, right, cnt = 0;
	float depth;
	while(scanf("%d", &n) == 1){
		if(n == 0) break;
		if(cnt != 0) printf("\n");
		data.resize(n + 1);
		for(int ix = 1; ix <= n; ++ix)
			scanf("%f %f %f %f %f", &data[ix].xpos, &data[ix].ypos,
				  &data[ix].width, &depth, &data[ix].height);
		res.clear();
		for(int ix = 1; ix <= n; ++ix){
			intersection.clear();
			for(int jx = 1; jx <= n; ++jx){
				if(data[ix].ypos <= data[jx].ypos) continue;
				if(data[ix].height > data[jx].height) continue;
				if(data[ix].xpos + data[ix].width <= data[jx].xpos) continue;
				if(data[ix].xpos >= data[jx].xpos + data[jx].width) continue;
				intersection.emplace_back(data[jx].xpos, data[jx].xpos + data[jx].width);
			}
			sort(intersection.begin(), intersection.end());
			if(intersection.empty()){
				res.push_back(ix);
				continue;
			}
			left = intersection[0].left;
			right = intersection[0].right;
			for(int ix = 1; ix != intersection.size(); ++ix){
				if(intersection[ix].left > right) break;
				if(intersection[ix].right > right)
					right = intersection[ix].right;
			}
			if(left > data[ix].xpos ||
			   right < data[ix].xpos + data[ix].width)
				res.push_back(ix);
		}
		sort(res.begin(), res.end(), cmp);
		printf("For map #%d, the visible buildings are numbered as follows:\n", ++cnt);
		printf("%d", res[0]);
		for(int ix = 1; ix != res.size(); ++ix)
			printf(" %d", res[ix]);
		printf("\n");
	}
	return 0;
}
