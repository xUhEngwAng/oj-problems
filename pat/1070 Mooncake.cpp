#include <algorithm>
#include <cstdio>
using namespace std;

/*
 * 这个题的收获是编码要严格按照题意来。比如每种月饼的存储量
 * 一开始我看输入的都是整数，就假定它是整数来处理了，所以一
 * 个测试点没有过。其实题目上没有说它是整数，只是说是一个正
 * 数而已。改成 float 立马就过了。
 */

struct cake{
	float total;     //total price
	float price;     //single price
	float store;     //storage

	bool operator<(cake two){
		return price > two.price;
	}
};

int main(){
	int N, D;
	scanf("%d %d", &N, &D);
	cake* datas = new cake[N];
	for(int ix = 0; ix != N; ++ix)
		scanf("%f", &datas[ix].store);
	for(int ix = 0; ix != N; ++ix){
		scanf("%f", &datas[ix].total);
		datas[ix].price = datas[ix].total / datas[ix].store;
	}
	sort(datas, datas + N);
	float count = 0;
	float profit = 0.0;
	for(int ix = 0; ix != N; ++ix){
		if(count + datas[ix].store <= D){
			count += datas[ix].store;
			profit += datas[ix].total;
		}
		else{
			profit += datas[ix].price * (D - count);
			count = D;
		}
		if(count >= D) break;
	}
	printf("%.2f\n", profit);
	return 0;
}
