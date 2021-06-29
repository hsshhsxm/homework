#include <iostream>
using namespace std;

#define PI 3.141592653589793

int N,F;
int radius[10010];
double space[10010];

bool judge(double r2){//判断派是否可以分成每个人得到的体积为r2
    int cnt = 0;
    for(int i = 0; i < N; ++i){
        cnt += space[i] / r2;
    }
    if(cnt >= F)
        return true;
    else 
        return false;
}

int main()
{
    cin >> N >> F;
    for(int i = 0; i < N; ++i){
        cin >> radius[i];
        space[i] = radius[i] * radius[i] *PI;
    }
    F += 1;
    double L = 0,R = space[0];
    for(int i = 0; i < N; ++i)
        if(space[i] > R)
            R = space[i];
    double res;
    while(R - L > 1e-6){
        double mid = L + (R - L) / 2;
        if(judge(mid)){
            res = mid;
            L = mid;
        }
        else 
            R = mid;
    }
    printf("%.3f\n", res);
    return 0;
}