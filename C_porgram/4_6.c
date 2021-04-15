#include <stdio.h>

int main(){
	for(int i = 1; i < 8; i+=2){
		for(int k = 0; k < (7 - i) / 2; k++)
			printf(" ");
		for(int j = 0; j < i; j++)
			printf("*");
		printf("\n");
	}
	for(int i = 7; i > 0; i-=2){
		for(int k = 0; k < (7 - i) / 2; k++)
			printf(" ");
		for(int j = 0; j < i; j++)
			printf("*");
		printf("\n");
	}
	return 0;
}
