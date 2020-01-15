#include <algorithm>
#include <vector>
#include <cstdio>

#define MAXDIST (C * davg)

using namespace std;

struct station{
	int dist;
	float price;

	station() = default;

	bool operator<(station two){
		return dist < two.dist;
	}
};

int C, D, davg, N;
station* sta;

void nextStation(int &pos, float& dist, float& totalPrice, float& gas){
    //printf("curr pos: %d, curr gas: %.2f\n", pos, gas);
	int next = pos + 1;
	float gasNeeded;
	if(sta[next].dist - sta[pos].dist > MAXDIST){
		dist += MAXDIST;
		pos = -1;
		return;
	}
	while(sta[next].dist - sta[pos].dist <= MAXDIST){
		if(sta[next++].price <= sta[pos].price)
			break;
	}
	next--;
	if(sta[next].price > sta[pos].price){
		next = pos + 1;
		dist += sta[next].dist - sta[pos].dist;
		totalPrice += (C - gas) * sta[pos].price;
		gas = C - (sta[next].dist - sta[pos].dist) / (float)davg;
		pos = next;
	}
	else{
		dist += sta[next].dist - sta[pos].dist;
		gasNeeded = (sta[next].dist - sta[pos].dist) / (float)davg;
		if(gasNeeded < gas) gas -= gasNeeded;
		else{
            totalPrice += (gasNeeded - gas) * sta[pos].price;
            gas = 0;
		}
		pos = next;
	}
	//printf("next station: %d\n", pos);
}

int main(){
	scanf("%d %d %d %d", &C, &D, &davg, &N);
	sta = new station[N + 1];
	for(int ix = 0; ix != N; ++ix)
		scanf("%f %d", &sta[ix].price, &sta[ix].dist);
    sta[N].price = 0, sta[N].dist = D;
	sort(sta, sta + N);
	if(sta[0].dist != 0){
        printf("The maximum travel distance = 0.00\n");
        return 0;
	}

	float currGas = 0.0, currDist = 0.0, currPrice = 0.0;
	int next, pos;
	for(pos = 0; pos < N;){
		nextStation(pos, currDist, currPrice, currGas);
		if(pos == -1) break;
	}
	if(pos == -1)
		printf("The maximum travel distance = %.2f\n", currDist);
	else printf("%.2f\n", currPrice);
	return 0;
}
