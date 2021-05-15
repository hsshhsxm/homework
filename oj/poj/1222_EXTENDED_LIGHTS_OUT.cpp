#include <iostream>
#include <cstring>
using namespace std;

int arrayIn[5][6];
int arrayOri[5][6];
int results[5][6] = {0};

void opposite(int i, int j){
    if(i >= 0 && j >= 0 && i < 5 && j < 6){
        arrayIn[i][j] = ~arrayIn[i][j];
    }
}

void press(int x, int y){
    opposite(x,y);
    opposite(x-1,y);
    opposite(x+1,y);
    opposite(x,y-1);
    opposite(x,y+1);
}

bool judge(){
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 6; ++j)
            if(arrayIn[i][j] == 0)
                return false;
    return true;
}

void out(){
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 6; ++j)
            cout << results[i][j];
}

void solution(){
    for(results[0][0] = 0; results[0][0] < 2; ++results[0][0])
        for(results[0][1] = 0; results[0][1] < 2; ++results[0][1])
            for(results[0][2] = 0; results[0][2] < 2; ++results[0][2])
                for(results[0][3] = 0; results[0][3] < 2; ++results[0][3])
                    for(results[0][4] = 0; results[0][4] < 2; ++results[0][4])
                        for(results[0][5] = 0; results[0][5] < 2; ++results[0][5]){
                            for(int i = 0; i < 6; ++i){
                                if(results[0][i] == 1)
                                    press(0, i);
                            }
                            for(int i = 1; i < 5; ++i){
                                int k = i - 1;
                                for(int j = 0; j < 6; ++j){
                                    if(arrayIn[k][j] == 1){
                                        press(i,j);
                                        results[i][j] = 1;
                                    }
                                    else 
                                        results[i][j] = 0;      
                                }
                            }
                            if(judge()){
                                out();
                            }
                            memcpy(arrayIn,arrayOri,sizeof(arrayOri));
                        }

}

int main(){
    int n;
    cin >> n;
    while(n){
        for(int i = 0; i < 5; ++i)
            for(int j = 0; j < 6; ++j){
                cin >> arrayOri[i][j];
                arrayIn[i][j] = arrayOri[i][j];
            }
        solution();
        n--;
    }
    return 0;
}