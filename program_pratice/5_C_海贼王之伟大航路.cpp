#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

const int inf = 100000;
int input[20][20];
int n, res;
int status[1<<17][20];

int solve(int x, int y){
    if(status[x][y] != inf || (x == 0 && y == 0))
        return status[x][y];
    if(y == 0)
        return inf;
    for (int i = 0; i < n; i++){
        int tmp = x & (1 << i);
        if(tmp)
            status[x][y] = min(status[x][y], solve(x - (1<<i), i)+input[i][y]);
    }
    return status[x][y];
}

int main(){
    cin >> n;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            cin >> input[i][j];
    for(int i = 1; i <= 1<<n; ++i)
        for(int j = 0; j <= n; ++j)
            status[i][j] = inf;
    cout << solve((1 << (n-1)) - 1, n-1) << endl;
    return 0;
}