#include <stdio.h>

int main(){
	int x;
	scanf("%d",&x);
	char str[6];
	sprintf(str,"%d",x);
	int count = 0;
	for(int i = 0; i < 6; i++){
		if(str[i])
			count ++;
	}
	printf("是 %d 位数\n",count);
	printf("单独输出每一位数字: ");
	for(int i = 0; i < count; i ++){
		printf("%c ",str[i]);
	}
	printf("\n");
	printf("逆序输出为: ");
	for(int i = 0; i < count; i++){
		printf("%c",str[count - i - 1]);
	}
	printf("\n");
	return 0;
}
