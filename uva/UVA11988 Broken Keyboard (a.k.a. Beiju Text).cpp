#include <string>
#include <iostream>
#include <list>
using namespace std;

/*
 * 此题是比较简单的，我是直接使用 std::list 来实现的。需要手动
 * 管理一个插入位置 pos，具体算法如下：
 * 
 * 1. 如果是正常字符，则将其插入 pos 之前的位置，并且将 pos 
 *    更新为被插入字符的后一位
 *
 *    pos = res.insert(pos, ch);
 *    ++pos
 *
 * 2. 如果是 '[' 或者 ']'，则更新 pos 为 res.begin() 或者 
 *    res.end()
 *
 * 这里只是需要注意 list.insert 的返回值，乃是指向被插入字符
 * 的迭代器，而 list.insert 本质上是 insert_before(it)，因
 * 此还要对返回的迭代器做自增运算。
 */

int main(){
	string str;
	list<char> res;
    list<char>::iterator pos;
	while(cin >> str){
		res.clear();
		pos = res.end();
		for(char ch : str){
            if(ch == '[') pos = res.begin();
            else if(ch == ']') pos = res.end();
            else{
                pos = res.insert(pos, ch);
                ++pos;
            }
		}
		for(char ch : res)
            cout << ch;
        cout << endl;
	}
	return 0;
}
