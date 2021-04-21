#include <stdio.h>

double func(int n,double x){
    if(n == 0)
        return 1;
    if(n == 1)
        return x;
    return ((2*n-1)*x*func(n-1,x) - (n-1)*func(n-2,x)) / n;
}

int main(){
    int n;
    double x;
    printf("输入n x：");
    scanf("%d%lf",&n,&x);
    printf("值为：%f\n",func(n,x));
    return 0;
}