#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

//大小2^n * 2^(n+1) 1024 * 2048
char map[1500][2500];

void draw(int x, int y, int n){
    if(n == 1){
        map[x][y+1]= map[x+1][y] = '/';
        map[x][y+2] = map[x+1][y+3] = '\\';
        map[x+1][y+1] = map[x+1][y+2] = '_';
        return;
    }
    int a = pow(2 , n-1), b = pow(2 , n);
    draw(x, y + b / 2, n - 1);
    draw(x + a, y, n - 1);
    draw(x + a, y + b, n - 1);
}


int main()
{
    int n;
    cin >> n;
    while(n != 0){
        memset(map, ' ', sizeof(map));
        draw(0,0,n);
        int a = pow(2 , n), b = pow(2 , n+1);
        for(int i = 0; i < a; ++i){
            map[i][b] = '\0';
            cout << map[i] << endl;
        }
        cout << endl;
        cin >> n;
    }
    return 0;
}

