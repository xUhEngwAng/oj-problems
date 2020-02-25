#include <string>
#include <iostream>
#include <cstdio>
using namespace std;

string valid = "0123456789.";

bool isvalid(const string &input){
	int pos = 0;
	if(input.front() == '+' || input.front() == '-')
		++pos;
	if(input.find_first_not_of(valid, pos) != -1)
		return false;
	pos = input.find('.');
	int count = 0;
	if(pos != -1){
		for(pos += 1; pos <= input.size(); ++pos){
			if(input[pos] == '.') return false;
			++count;
		}
	}
	if(count > 3) return false;
	double res = stod(input);
	if(res < -1000 || res > 1000) return false;
	return true;
}

int main(){
	int N, count = 0;
	cin >> N;
	string input;
	double res = 0.0;
	while(N--){
		cin >> input;
		if(!isvalid(input)){
			cout << "ERROR: " << input << ' '
		         << "is not a legal number" << endl;
			continue;
		}
		count++;
		res += stod(input);
	}
	printf("The average of ");
	if(count == 0)
		printf("0 numbers is Undefined\n");
	else if(count == 1)
		printf("1 number is %.2f\n", res);
	else
		printf("%d numbers is %.2f\n", count, res / count);
	return 0;
}
