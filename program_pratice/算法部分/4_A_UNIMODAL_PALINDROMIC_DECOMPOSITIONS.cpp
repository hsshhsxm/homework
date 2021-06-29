#include <iostream>
#include <cstring>
using namespace std;

long long num[300][300];

long long dp(int n){
    memset(num, 0, sizeof(num));
    for(int i = 0; i < 250; ++i)
        for(int j = 0; j < 250; ++j){
            if(i == 0)
                num[i][j] = 1;
            else if(j > i)
                num[i][j] = 0;
            else 
                num[i][j] = 1;
        }
    for(int i = 2; i < n + 1; ++i)
        for(int j = i / 2; j > 0; --j)
            num[i][j] = num[i - 2 * j][j] + num[i][j + 1];
    return num[n][1];
}

int main()
{
    int n;
    cin >> n;
    while(n != 0){
        cout << n << " " << dp(n) << endl;
        cin >> n;
    }
    return 0;
}