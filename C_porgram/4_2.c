#include <stdio.h>

int main(){
	int x,y;
	printf("x=");
	scanf("%d",&x);
	if(x > 30){
		y = 8 * x - 216;
	} else if(x>=10 && x <=30){
		y = 2 * x + 3;
	} else{
		y = -(5 * x - 24);
	}
	printf("y=%d",y);
	return 0;
}
