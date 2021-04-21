#include <stdio.h>
#include <math.h>

double fx(double  a,double  b, double  c, double  d, double x){
    return a*x*x*x + b*x*x + c*x + d;
}

double fx1(double  a,double  b, double  c, double  x){
    return 3*a*x*x + 2*b*x + c;
}

double func(int a,int b, int c, int d){
    double xi1,xi2;
    xi1 = 1;
    xi2 = xi1 - fx(a,b,c,d,xi1)/fx1(a,b,c,xi1);
    while(fabs(xi2-xi1) > 1e-5){
        xi1 = xi2;
        xi2 = xi1 - fx(a,b,c,d,xi1)/fx1(a,b,c,xi1);
    }
    return xi2;
}

int main(){
    int a,b,c,d;
    printf("输入参数a,b,c,d：");
    scanf("%d%d%d%d",&a,&b,&c,&d);
    double result = func(a,b,c,d);
    printf("根为：%f\n",result);
    return 0;
}