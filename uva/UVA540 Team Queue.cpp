#include <cstdio>
#include <deque>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * 难以想象这种水题我在两个月前居然不会做！看来最近的练习还是
 * 取得了一定的进步的。
 *
 * 此题我的思路和紫书上参考答案的思路基本是相同的，及采用两种
 * 队列作为底层结构，一个是全局的队列，一个是每个队伍的队列。
 * 我这里的实现是 deque of deque，而参考的解答中全局队列只存
 * 储队伍号，这种实现是更加优化的，比我的实现好，应该学习。
 *
 * 我这里还犯了一个低级错误，当不存在与新入队的元素同组的元素时，
 * 需要建立一个新的队列放在整体队列的最后面，我居然用 
 * deque<int>(curr) 想要初始化只有一个元素 curr 的 deque？！
 * 这 tm 直接给我创建了 curr 个为零的元素，我还找了半天 bug。
 */

deque<deque<int>> queue;
vector<int> team_pos(1000);
vector<int> team_hash(1000000);

int main(){
	//freopen("1.out", "w", stdout);
	int t, cnt = 0, num, curr;
	char cmd[8];
	while(true){
		scanf("%d", &t);
		if(t == 0) break;
		queue.clear();
		fill(team_pos.begin(), team_pos.end(), -1);
		for(int ix = 0; ix != t; ++ix){
			scanf("%d", &num);
			while(num--){
				scanf("%d", &curr);
				team_hash[curr] = ix;
			}
		}
		printf("Scenario #%d\n", ++cnt);
		while(true){
			scanf("%s", cmd);
			if(cmd[0] == 'S') break;
			if(cmd[0] == 'E'){
				scanf("%d", &curr);
				num = team_hash[curr];
				if(team_pos[num] == -1){
					queue.push_back(deque<int>());
					queue.back().push_back(curr);
					team_pos[num] = queue.size() - 1;
				}
				else
					queue[team_pos[num]].push_back(curr);
				/*
				for(int e : queue[team_pos[num]])
					printf("%d ", e);
				printf("\n");*/
			}
			else{
				curr = queue[0][0];
				printf("%d\n", curr);
				queue[0].pop_front();
				if(queue[0].empty()){
					queue.pop_front();
					for(int ix = 0; ix != team_pos.size(); ++ix)
						if(team_pos[ix] != -1)
							team_pos[ix]--;
				}
			}
		}
		printf("\n");
	}
	return 0;
}
