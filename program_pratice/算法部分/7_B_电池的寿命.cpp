#include <iostream>
#include <algorithm>
using namespace std;

int N;
int battery[1005];

int main()
{
    while(~scanf("%d",&N)){
        int sum = 0;
        for(int i = 0; i < N; ++i){
            cin >> battery[i];
            sum += battery[i];
        }
            
        sort(battery, battery + N);
        int maxBattary = battery[N-1];
        double res;
        if(maxBattary > sum - maxBattary)//最大电量的电池大于其他电池电量之和
            res = sum - maxBattary;
        //最大电量的电池电量小于其他电池之和，不关系怎么划分，总能用完
            //把最大的电池拿出来，将其他的电池一点一点消耗到和这枚电池一样，然后全部用掉
        //因为电池成对使用，故答案为总电量除以2
        else 
            res = sum / 2.0;
        printf("%.1f\n", res);
    }
    return 0;
}