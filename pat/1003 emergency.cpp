#include <stdio.h>
#include <stdlib.h>

#define MAXNUM     9999
#define MAXCITYNUM 100
#define TRUE       1
#define FALSE      0

struct road;
struct city;
struct distance;
typedef road *Road;
typedef city *City;
typedef distance *Distance;

struct road {
	short int nextCity;
	short int length;
	Road next;
};

struct city {
	short int rescueNum;
	Road connectedCity;
};

struct distance {
	short int roadLen;
	short int isValid;
};

short int findPath(City allCity, short int origin, short int dest);
short int findMinDistance(Distance distances, short int n);

int main() {
	short int cityNum, roadNum, currCity, rescueCity;
	scanf("%hd %hd %hd %hd", &cityNum, &roadNum, &currCity, &rescueCity);

	City allCity = (City)malloc(sizeof(city)*cityNum);
	for (short int ix = 0; ix < cityNum; ix++) {
		scanf("%hd", &allCity[ix].rescueNum);
		//initialize allCity[ix].connectedCity
		allCity[ix].connectedCity = NULL;
	}

	short int firstCity, secondCity, roadLength;
	Road tempPath;
	for (short int ix = 0; ix < roadNum; ix++) {
		scanf("%hd %hd %hd", &firstCity, &secondCity, &roadLength);

		//head insert
		tempPath = (Road)malloc(sizeof(road));
		if(tempPath == NULL) return -1;

		tempPath->nextCity = secondCity;
		tempPath->length   = roadLength;
		tempPath->next = allCity[firstCity].connectedCity;
		allCity[firstCity].connectedCity = tempPath;

		tempPath = (Road)malloc(sizeof(road));
		if(tempPath == NULL) return -1;

		tempPath->nextCity = firstCity;
		tempPath->length   = roadLength;
		tempPath->next = allCity[secondCity].connectedCity;
		allCity[secondCity].connectedCity = tempPath; 
	}

	Road currRoad;
	for(short int ix = 0; ix < cityNum; ix++){
		printf("%hd: ", ix);
		currRoad = allCity[ix].connectedCity;
		while(currRoad!=NULL){
			printf("%hd,%hd ", currRoad->nextCity, currRoad->length);
			currRoad = currRoad->next;
		}
		printf("\n");
	}


	short int *paths;
	Distance distances;
	paths = (short int*)malloc(sizeof(currCity)*cityNum);
	distances = (Distance)malloc(sizeof(distance)*(cityNum));

	//initialize distances & paths
	for (short int ix = 0; ix < cityNum; ix++) {
		distances[ix].roadLen = findPath(allCity, currCity, ix);
		distances[ix].isValid = TRUE;

		paths[ix] = currCity;
	}

	//main loop: update distances & paths
	short int minPos;
	short int currLength;
	while ((minPos = findMinDistance(distances, cityNum)) != -1) {
		//if (minPos == rescueCity) break;
		//else
		for (short int ix = 0; ix < cityNum; ix++) {
			if (distances[ix].isValid && ix != minPos) {
				currLength = findPath(allCity, minPos, ix) +
					distances[minPos].roadLen;
				if (currLength < distances[ix].roadLen) {//update
					distances[ix].roadLen = currLength;
					paths[ix] = minPos;
				}
			}
		}
	}
	for(short int ix = 0; ix < cityNum; ix ++)
		if(ix !=  currCity)
			printf("%hd ", distances[ix].roadLen);

	system("pause");

	return 0;
}

//return the path length of two given cities
short int findPath(City allCity, short int origin, short int dest) {
	//assume a valid input
	Road currRoad = allCity[origin].connectedCity;
	while (currRoad != NULL) {
		if (currRoad->nextCity == dest) return currRoad->length;
		//else
		currRoad = currRoad->next;
	}
	//do not exist a road
	return MAXNUM;
}

//return postion of mininal distance
short int findMinDistance(Distance distances, short int n) {
	short int minPos = -1, minDist = MAXNUM;
	distance currDist;
	for (short int ix = 0; ix < n; ix++) {
		currDist = distances[ix];
		if (currDist.isValid) {
			if (currDist.roadLen < minDist) {
				minDist = currDist.roadLen;
				minPos = ix;
			}
			//else pass
		}
		//else pass
	}
	if (minPos != -1) distances[minPos].isValid = FALSE;

	return minPos;
}