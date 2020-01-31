#include <cstdio>

int main(){
	int galleon1, galleon2, galleon;
	int sickle1, sickle2, sickle;
	int knut1, knut2, knut;
	scanf("%d.%d.%d", &galleon1, &sickle1, &knut1);
	scanf("%d.%d.%d", &galleon2, &sickle2, &knut2);
	int carry = 0;
	knut = knut1 + knut2;
	if(knut >= 29){
		knut -= 29;
		carry = 1;
	}
	sickle = sickle1 + sickle2 + carry;
	if(sickle >= 17){
		sickle -= 17;
		carry = 1;
	}else carry = 0;
	galleon = galleon1 + galleon2 + carry;
	printf("%d.%d.%d\n", galleon, sickle, knut);
	return 0;
}
