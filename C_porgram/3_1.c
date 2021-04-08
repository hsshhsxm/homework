#include <stdio.h>

int main(){
    int a=3,b=4,c=5;
    double x=1.72,y=2.4,z=-3.6;
    long u=51274,n=128365;
    char c1='a',c2='A';
    printf("a= %d  b= %d  c= %d\n",a,b,c);
    printf("x=%.7lf,y=%.7lf,z=%.7lf\n",x,y,z);
    printf("x+y= %.2lf  y+z=%.2lf  z+x=%.2lf\n",x+y,y+z,z+x);
    printf("u= %ld  n=   %ld\n",u,n);
    printf("c1='%c' or %d(ASCII)\n",c1,c1);
    printf("c2='%c' or %d(ASCII)\n",c2,c2);
    return 0;
}