#include <stdio.h>

int main(){
	char str[4];
	int a,b,c;
	for(int i = 100; i < 1000 ; i++){
		sprintf(str,"%d",i);
		a = str[0] - '0';
		b = str[1] - '0';
		c = str[2] - '0';
		if(i == a*a*a + b*b*b + c*c*c)
			printf("%d ",i);
	}
	printf("\n");
	return 0;
}
