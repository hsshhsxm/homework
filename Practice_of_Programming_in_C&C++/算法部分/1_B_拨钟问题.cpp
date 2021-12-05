#include <iostream>
using namespace std;

int main(){
    int clockArray[9];
    for(int i = 0; i < 9; ++i)
        cin >> clockArray[i];
    int op[9] = {0};
    int state[9] = {0};
    for(op[0] = 0; op[0] < 4; ++op[0])
        for(op[1] = 0; op[1] < 4; ++op[1])
            for(op[2] = 0; op[2] < 4; ++op[2])
                for(op[3] = 0; op[3] < 4; ++op[3])
                    for(op[4] = 0; op[4] < 4; ++op[4])
                        for(op[5] = 0; op[5] < 4; ++op[5])
                            for(op[6] = 0; op[6] < 4; ++op[6])
                                for(op[7] = 0; op[7] < 4; ++op[7])
                                    for(op[8] = 0; op[8] < 4; ++op[8]){
                                        state[0] = (clockArray[0] + op[0] + op[1] + op[3]) % 4;//A
                                        state[1] = (clockArray[1] + op[0] + op[1] + op[2] + op[4]) % 4;//B
                                        state[2] = (clockArray[2] + op[1] + op[2] + op[5]) % 4;//C
                                        state[3] = (clockArray[3] + op[0] + op[3] + op[4] + op[6]) % 4;//D
                                        state[4] = (clockArray[4] + op[0] + op[2] + op[4] + op[6] + op[8]) % 4;//E
                                        state[5] = (clockArray[5] + op[2] + op[4] + op[5] + op[8]) % 4;//F
                                        state[6] = (clockArray[6] + op[3] + op[6] + op[7]) % 4;//G
                                        state[7] = (clockArray[7] + op[4] + op[6] + op[7] + op[8]) % 4;//H
                                        state[8] = (clockArray[8] + op[5] + op[7] + op[8]) % 4;//I
                                        int sum = 0;
                                        for(int i = 0; i < 9; ++i)
                                            sum += state[i];
                                        if(sum == 0){
                                            for(int i = 0; i < 9; ++i){
                                                while(op[i]--)
                                                    cout << i+1 << " ";
                                            }
                                            cout << endl;
                                            return 0;
                                        }
                                    }
    return 0;
}