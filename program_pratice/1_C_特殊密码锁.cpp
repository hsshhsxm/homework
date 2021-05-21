#include <iostream>
#include <string>
using namespace std;

int block[32] = {0};
int tlock[32] = {0};

void patch(int i){
    (block[i] == 0) ? block[i] = 1 : block[i] = 0;
    (block[i-1] == 0) ? block[i-1] = 1 : block[i-1] = 0;
    (block[i+1] == 0) ? block[i+1] = 1 : block[i+1] = 0;
}

int main(){
    string origin, target;
    cin >> origin >> target;
    int size = origin.size();
    for(int i = 1; i < size + 1; ++i)
        block[i] = origin.at(i-1) - '0';
    for(int i = 1; i < size + 1; ++i)
        tlock[i] = target.at(i-1) - '0';
    for(int i = 1; i < size + 1; ++i){
        if(block[i] != tlock[i] && block[i+1] != tlock[i+1]){
            
        }
    }
    return 0;
}