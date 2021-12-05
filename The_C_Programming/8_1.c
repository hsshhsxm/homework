#include <stdio.h>

int main(){
    int a[10000] = {0};
    int n;
    printf("输入n：");
    scanf("%d", &n);
    int count = 0;
    int left = n;
    int i = 0;
    while(left > 1){
        if(*(a + i) == 0)
            count++;
        if(count == 5){
            count = 0;
            *(a+i) = 1;
            left--;
        }
        if(i == n-1)
            i = 0;
        else 
            i++;
    }
    for(int i = 0; i < n; ++i)
        if(*(a + i) == 0)
            printf("最后一人的编号：%d\n", i + 1);
    return 0;
}