#include <stdio.h>

int countNum(char * start, char * end){
    int sum = 0;
    int k = 0;
    while(end != start){
        int tmp = 1;
        for(int i = 0; i < k; ++i)
            tmp *= 10;
        sum += tmp * ((*end) - '0');
        end--;
        k++;
    }
    int tmp = 1;
    for(int i = 0; i < k; ++i)
        tmp *= 10;
    sum += tmp * ((*end) - '0');
    return sum;
}

int main(){
    int a[10000];
    int count = 0;
    char str[10000];
    scanf("%s",str);
    char * start = str;
    char * end;
    char * pos = str;
    while(*pos != '\0'){
        if(*pos >= '0' && *pos <= '9'){
            if( *(pos-1) <'0' || *(pos-1) > '9')
                start = pos;
            if((*(pos+1) == '\0') || (*(pos+1) <'0' || *(pos+1) > '9')){
                end = pos;
                a[count++] = countNum(start, end);
            }
            ++pos;
        }
        else{
            ++pos;
        }
    }
    printf("总共有%d个整数，分别为：\n", count);
    for(int i = 0; i < count; ++i)
        printf("%d ",a[i]);
    printf("\n");
}