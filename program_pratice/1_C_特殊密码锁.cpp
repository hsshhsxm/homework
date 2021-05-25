#include <iostream>
#include <string>
using namespace std;

int block[32] = {0};
int olock[32] = {0};
int tlock[32] = {0};
int size;

void patch(int i){
    //cout << "patch " << i << endl;
    (block[i] == 0) ? block[i] = 1 : block[i] = 0;
    (block[i-1] == 0) ? block[i-1] = 1 : block[i-1] = 0;
    (block[i+1] == 0) ? block[i+1] = 1 : block[i+1] = 0;
    //for(int i = 1; i < size + 1; ++i)
    //    cout << block[i];
    //cout << endl;
}

void reset(){
    for(int i = 0; i < 32; ++i)
        block[i] = olock[i];
}

bool judge(){
    for(int i = 1; i < size + 1; ++i)
        if(block[i] != tlock[i])
            return false;
    return true;
}

int solve(){
    int minStep = 0;
    //第一个不按
    int step = 0;
    for(int i = 1; i < size; ++i){
        if(block[i] != tlock[i]){
            patch(i+1);
            ++step;
        }
    }
    if(judge())
        minStep = step; 
    step = 0;
    reset();
    //第一个按下
    patch(1);
    ++step;
    for(int i = 1; i < size; ++i){
        if(block[i] != tlock[i]){
            patch(i+1);
            ++step;
        }
    }
    if(judge()){
        if(minStep == 0)
            minStep = step;
        if(minStep > step)
            minStep = step;
    }
    return minStep;
}


int main(){
    string origin, target;
    cin >> origin >> target;
    size = origin.size();
    for(int i = 1; i < size + 1; ++i){
        block[i] = origin.at(i-1) - '0';
        olock[i] = block[i];
    }
    for(int i = 1; i < size + 1; ++i)
        tlock[i] = target.at(i-1) - '0';
    int r = solve();
    (r == 0) ? (cout << "impossible" << endl) : (cout << r << endl);
    return 0;
}