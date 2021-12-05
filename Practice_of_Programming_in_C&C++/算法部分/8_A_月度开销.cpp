#include <iostream>
#include <algorithm>
using namespace std;

int n,m;
int cost[100005];

bool judge(int max){//检测分为m端，每段最大开销为max是否可行
    int count = 1;
    int sum = 0;
    for(int i = 0; i < n; ++i){
        if(count > m)
            return false;
        if(sum + cost[i] <= max){
            sum += cost[i];
        }
        else{
            count++;
            sum = cost[i];
        }
    }
    return true;
}

int main()
{
    cin >> n >> m;
    for(int i = 0; i < n; ++i)
        cin >> cost[i];
    int R = 0,L = 0;
    for(int i = 0; i < n; ++i)
        R += cost[i];
    for(int i = 0; i < n; ++i)
        if(cost[i] > L)
            L = cost[i];
    int minNum;
    while (L <= R){
        int mid = L + (R - L) / 2;
        if(judge(mid)){
            minNum = mid;
            R = mid - 1;
        }
        else 
            L = mid + 1;
    }
    cout << minNum << endl;
    return 0;
}