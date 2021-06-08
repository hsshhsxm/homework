#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int a[205]; //钱的种类
int b[205]; //必须有的钱的种类
int dp[10000 * 101];//形成i元礼物的方案
int dpNoI[10000 * 101]; //没有j时，形成i元礼物的方案

int main()
{
    memset(a, 0 ,sizeof(a));
    memset(b, 0 ,sizeof(b));
    memset(dp, 0 ,sizeof(dp));
    memset(dpNoI, 0 ,sizeof(dpNoI));
    int n,x;
    cin >> n >> x;
    for(int i = 0; i < n; ++i)
        cin >> a[i];
    dp[0] = 1;
    for(int i = 0; i < n; ++i)
        for(int j = x; j >= a[i]; --j)
            dp[j] = dp[j] + dp[j - a[i]];
    int cnt = 0;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < x + 1; ++j){
            if(j < a[i])
                dpNoI[j] = dp[j];
            else 
                dpNoI[j] = dp[j] - dpNoI[j - a[i]];
        }
        if(dpNoI[x] == 0){
            b[cnt] = a[i];
            ++cnt;
        }
    }
    if(cnt == 0)
        cout << 0 << endl << endl;
    else{
        cout << cnt << endl;
        for(int i = 0; i < cnt; ++i)
            cout << b[i] << " ";
        cout << endl;
    }
    return 0;
}