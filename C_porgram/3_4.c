#include <stdio.h>

int main(){
    double f;
    scanf("请输入华氏度：%lf",&f);
    double c;
    c = (f - 32) * 5 / 9;
    printf("对应的摄氏温度为：%.2lf",c);
    return 0;
}