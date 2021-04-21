#include <stdio.h>

int main(){
    int a[8][8];
    a[0][0] = 1;
    for(int i = 0; i < 8; ++i){
        a[i][0] = 1;
        a[i][i] = 1;
    }
    for(int i = 1; i < 8; ++i){
        for(int j = 1; j < i; ++j){
            a[i][j] = a[i-1][j] + a[i-1][j-1];
        }
    }
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < i + 1; ++j)
            printf("%d ",a[i][j]);
        printf("\n");
    }
    return 0;
}