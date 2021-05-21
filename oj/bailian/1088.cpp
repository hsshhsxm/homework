#include <iostream>
#include <algorithm>
using namespace std;

int region[102][102] = {0};
int road[102][102] = {0};
int R,C;

int f(int i, int j){
    if(road[i][j])
        return road[i][j];
    road[i][j] = 1;
    if(region[i][j] > region[i-1][j] && i > 1)
        road[i][j] = max(road[i][j], f(i-1,j)+1);
    if(region[i][j] > region[i][j-1] && j > 1)
        road[i][j] = max(road[i][j], f(i,j-1)+1);
    if(region[i][j] > region[i+1][j] && i < R)
        road[i][j] = max(road[i][j], f(i+1,j)+1);
    if(region[i][j] > region[i][j+1] && j < C)
        road[i][j] = max(road[i][j], f(i,j+1)+1);
    return road[i][j];
}

int main(){
    cin >> R >> C;
    for(int i = 0; i < R; ++i)
        for(int j = 0; j < C; ++j)
            cin >> region[i+1][j+1];
    int max = 0;
    for(int i = 1; i <= R; ++i)
        for(int j = 1; j <= C; ++j)
            if(f(i,j) > max)
                max = f(i,j);
    cout << max << endl;
    return 0;
}