#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRLEN 16
#define TIMELEN 9

int main(){
    short int total;
    char userId[STRLEN], currSignIn[TIMELEN],currSignOut[TIMELEN];
    char firstId[STRLEN], lastId[STRLEN];
    short int currHour, currMin, currSnd;
    short int firstInHour=24, firstInMin=60, firstInSnd=60;
    short int lastOutHour=0, lastOutMin=0, lastoutSnd=0;

    scanf("%hd", &total);

    for(short int ix = 0; ix < total; ix++){
        scanf("%s %s %s",userId,currSignIn, currSignOut); 
        //sign in
        currHour = (currSignIn[0]-'0')*10+currSignIn[1]-'0';
        currMin  = (currSignIn[3]-'0')*10+currSignIn[4]-'0';
        currSnd  = (currSignIn[6]-'0')*10+currSignIn[7]-'0';

        if(currHour < firstInHour){//update
        	firstInHour = currHour;
        	firstInMin  = currMin;
        	firstInSnd  = currSnd;
        	strcpy(firstId,userId);
        }else
        if(currHour == firstInHour){
        	if(currMin < firstInMin){
        		firstInMin  = currMin;
        		firstInSnd  = currSnd;
        		strcpy(firstId,userId);
        	}else
        	if(currMin == firstInMin){
        		if(currSnd < firstInSnd){
        			firstInSnd  = currSnd;
        			strcpy(firstId,userId);
        		}
        		//else pass
        	}
        	//else pass
        }
        //else pass

        //sign out
        currHour = (currSignOut[0]-'0')*10+currSignOut[1]-'0';
        currMin  = (currSignOut[3]-'0')*10+currSignOut[4]-'0';
        currSnd  = (currSignOut[6]-'0')*10+currSignOut[7]-'0';

        if(currHour > lastOutHour){//update
        	lastOutHour = currHour;
        	lastOutMin  = currMin;
        	lastoutSnd  = currSnd;
        	strcpy(lastId,userId);
        }else
        if(currHour == lastOutHour){
        	if(currMin > lastOutMin){
        		lastOutMin  = currMin;
        		lastoutSnd  = currSnd;
        		strcpy(lastId,userId);
        	}else
        	if(currMin == lastOutMin){
        		if(currSnd > lastoutSnd){
        			lastoutSnd  = currSnd;
        			strcpy(lastId,userId);
        		}
        		//else pass
        	}
        	//else pass
        }
        //else pass
    }
  	printf("%s %s", firstId, lastId);
    

    return 0;
}
