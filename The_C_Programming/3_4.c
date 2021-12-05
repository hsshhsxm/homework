#include <stdio.h>

int main(){
    double f;
    printf("请输入华氏度：");
    scanf("%lf",&f);
    double c;
    c = (f - 32) * 5 / 9;
    printf("对应的摄氏温度为：%.2lf\n",c);
    return 0;
}