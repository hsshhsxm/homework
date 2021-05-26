#include <iostream>
using namespace std;

int a[40] = {0};
int way[50][40]; //way[i][j]表示从前j种物品里凑体积i的方法数

int main(){
    int N;
    cin >> N;
    for(int i = 0; i < 50; ++i)
        for(int j = 0; j < 40; ++j)
            way[i][j] = 0;
    for(int i = 1; i <= N; ++i){
        cin >> a[i];
        way[0][i] = 1;
    }
    way[0][0] = 1;
    for(int i = 1; i <= 40; ++i)
        for(int j = 1; j <= N; ++j){
            way[i][j] = way[i][j-1];
            if(i - a[j] >= 0)
                way[i][j] += way[i-a[j]][j-1];
            //if(i == 40)
                //printf("::way[%d][%d] = %d\n", i - a[j], j-1, way[i-a[j]][j-1]);
            //printf("way[%d][%d] = %d\n", i, j, way[i][j]);
        }
    cout << way[40][N] << endl;
    return 0;
}