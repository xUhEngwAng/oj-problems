#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct entry;
int H, L;
vector<entry> datas;

enum Type{LOW, FOOL, NOBLE, SAGE};

struct entry{
	int id;
	int virtue;
	int talent;
	Type type;

	entry() = default;
	entry(int id, int virtue, int talent): id(id), virtue(virtue), talent(talent){
		if(virtue >= H && talent >= H) type = SAGE;
		else if(virtue >= H && talent >= L) type = NOBLE;
		else if(virtue >= talent) type = FOOL;
		else type = LOW;
	}
};

bool cmp(entry& one, entry& two){
	if(one.type != two.type) return one.type > two.type;
	if(one.virtue + one.talent != two.virtue + two.talent)
		return one.virtue + one.talent > two.virtue + two.talent;
	if(one.virtue != two.virtue) return one.virtue > two.virtue;
	return one.id < two.id;
}

int main(){
	int N, id, virtue, talent;
	scanf("%d %d %d", &N, &L, &H);
	datas.reserve(N);
	for(int ix = 0; ix != N; ++ix){
		scanf("%d %d %d", &id, &virtue, &talent);
		if(virtue >= L && talent >= L)
			datas.emplace_back(id, virtue, talent);
	}
	sort(datas.begin(), datas.end(), cmp);

	printf("%d\n", datas.size());
	for(auto entry : datas)
		printf("%d %d %d\n", entry.id, entry.virtue, entry.talent);
	return 0;
}
