#include <stdio.h>

int main(){
    char str[12][10] = {"January", "February", "March", "April", "May",
    "June", "July", "August", "September", "October", "November", "December"};
    int n;
    printf("输入月份号：");
    scanf("%d",&n);
    printf("月份英文名为：%s\n", *(str+n-1));
    return 0;
}