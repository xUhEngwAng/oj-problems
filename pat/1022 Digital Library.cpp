#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdio.h>
using namespace std;
struct book{
	int id;
	string title;
	string author;
	vector<string> keyWords;
	string publisher;
	int year;
};
int main(){
	int Num;
	scanf("%d", &Num);
	vector<book> library(Num);
	string keywords;
	for(int ix = 0; ix != Num; ix++){ // input data
		scanf("%d\n", &library[ix].id);
		getline(cin, library[ix].title);
		getline(cin, library[ix].author);
		getline(cin, keywords);
		for(int front = 0, behind = 0;;front = behind+1){
			behind = keywords.find(' ', front);
			if (behind == keywords.npos) {
				library[ix].keyWords.push_back(keywords.substr(front));
				break;
			}
			library[ix].keyWords.push_back(keywords.substr(front, behind-front));
		}
		getline(cin, library[ix].publisher);
		scanf("%d", &library[ix].year);
	}
	sort(library.begin(), library.end(), [](book book1, book book2) {return book1.id < book2.id; });
	int queryNum, querytype, flag;
	scanf("%d\n", &queryNum);
	string queryInfo, query;
	for(int ix = 0; ix != queryNum; ix++){
		flag = 0;
		getline(cin, queryInfo);
		querytype = queryInfo[0];
		query = queryInfo.substr(3);
		cout << queryInfo << endl;
		switch(querytype){
		case '1'://title
			for_each(library.cbegin(), library.cend(), [query, &flag](book oneEntry) 
			{if (oneEntry.title == query) { printf("%07d\n", oneEntry.id), flag = 1; } });
			break;
		case '2'://author
			for_each(library.cbegin(), library.cend(), [query, &flag](book oneEntry)
			{if (oneEntry.author == query) { printf("%07d\n", oneEntry.id), flag = 1; } });
			break;
		case '3'://one keyword
			for_each(library.cbegin(), library.cend(), [query, &flag](book oneEntry)
			{if (find(oneEntry.keyWords.cbegin(), oneEntry.keyWords.cend(), query) != oneEntry.keyWords.cend()) { printf("%07d\n", oneEntry.id), flag = 1; } });
			break;
		case '4'://publisher
			for_each(library.cbegin(), library.cend(), [query, &flag](book oneEntry)
			{if (oneEntry.publisher == query) { printf("%07d\n", oneEntry.id), flag = 1; } });
			break;
		case '5'://year
			for_each(library.cbegin(), library.cend(), [query, &flag](book oneEntry)
			{if (oneEntry.year == stoi(query)) { printf("%07d\n", oneEntry.id), flag = 1; } });
			break;
		}
		if (!flag) printf("Not Found\n");
	}
	return 0;
}
