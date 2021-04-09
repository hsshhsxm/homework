#include <stdio.h>

#define PI 3.14

int main(){
    double r, h;
    printf("请输入半径与高（空格隔开）：\n");
    scanf("%lf %lf",&r,&h);
    double circlePerimeter,circleArea,ballArea,ballVolume,cylinderVolume;
    circlePerimeter = 2 * PI * r;
    circleArea = PI * r * r;
    ballArea = 4 * PI * r * r;
    ballVolume = PI * r * r * r;
    cylinderVolume = PI * r * r * h;
    printf("圆周长：%.2lf\n",circlePerimeter);
    printf("圆面积：%.2lf\n",circleArea);
    printf("球表面积：%.2lf\n",ballArea);
    printf("球体积：%.2lf\n",ballVolume);
    printf("圆柱体积：%.2lf\n",cylinderVolume);
    return 0;
}