#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

bool paddy[5000][5000] = {false};
int R,C;
int maxStep = 3;

void judge(int x1, int y1, int x2, int y2){
    int dx = x2 - x1;
    int dy = y2 - y1;
    if(x1 - dx >= 0 && y1 - dy >= 0)
        return;
    if(x1 + dx * (maxStep - 1) > C - 1 || y1 + dy * (maxStep - 1) > R - 1)
        return;
    int tmpStep = 2;
    int status = true;
    while(status){
        if(paddy[x1 + tmpStep * dx][y1 + tmpStep * dy])
            tmpStep++;
        else 
            status = false;
    }
    if(maxStep < tmpStep)
        maxStep = tmpStep;
}

void solution(){
    for(int i = 0; i < R; ++i){
        for(int j = 0; j < C; ++j){
            if(paddy[i][j]){
                for(int k = i; k < R; ++k){
                    for(int m = 0; m < C; ++m){
                        if(paddy[k][m])
                            if(k!=i || m!=j)
                                judge(i,j,k,m);
                    }
                }
            }
        }
    }
}

int main(){
    scanf("%d%d",&R, &C);
    int N, m, n;
    scanf("%d",&N);
    while(N){
        scanf("%d%d",&m, &n);
        paddy[m-1][n-1] = true;
        N--;
    }
    solution();
    printf("%d",maxStep);
    return 0;
}