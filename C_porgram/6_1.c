#include <stdio.h>

#define MAXBUFFER 256

void findMaxStr(char * str){
    int maxCount = 0,tmpCount = 0, begin = 0;
    for(int i = 0; i < MAXBUFFER; ++i){
        if((str[i] <= 'z' && str[i] >= 'a') || (str[i] <= 'Z' && str[i] >= 'A')){
            tmpCount += 1;
        } else if(str[i] == ' '){
            if(tmpCount > maxCount){
                begin = i - tmpCount;
                maxCount = tmpCount;
            }
            tmpCount = 0;
        } else{
            break;
        }
   }
   for(int i = 0; i < maxCount; ++i){
       printf("%c",str[begin + i]);
   }
   printf("\n");
}

int main(){
    char str[MAXBUFFER];
    gets(str);
    findMaxStr(str);
    return 0;
}