#include <string>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <map>
#include <set>
using namespace std;
struct node{
	int value;
	int Next;
};
int main(){
	int start, N, pos;
	scanf("%d %d", &start, &N);
	map<int, node> list;
	int addr;
	node tmpNode;
	for(int ix = 0; ix != N; ix++){
		scanf("%d %d %d", &addr, &tmpNode.value, &tmpNode.Next);
		list[addr] = tmpNode;
	}
	set<int> values;
	int currValue;
	vector<node> deleted;
	node tmp;
	for(pos = start; pos != -1;pos = list[pos].Next){
		currValue = fabs(list[pos].value);
		if (values.find(currValue) == values.end()) {
			values.insert(currValue);
			if(pos == start) printf("%05d %d", pos, list[pos].value);
			else printf(" %05d\n%05d %d", pos, pos, list[pos].value);
		}
		else{
			tmp.value = list[pos].value;
			tmp.Next  = pos;
			deleted.push_back(tmp);
		}
	}
	printf(" -1\n");
	for(auto It = deleted.cbegin(); It != deleted.cend(); *It++){
		if (It == deleted.cbegin())	printf("%05d %d", It->Next, It->value);
		else printf(" %05d\n%05d %d", It->Next, It->Next, It->value);
	}
	if(!deleted.empty()) printf(" -1\n");
	system("pause");
	return 0;
}
