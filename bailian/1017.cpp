#include <iostream>
using namespace std;

int main()
{
    int a[6];
    while(true){
        int sum = 0;
        for(int i = 0; i < 6; ++i){
            cin >> a[i];
            sum += a[i];
        }
        if(sum == 0)
            break;
        int boxNum = 0;
        boxNum = a[5] + a[4] + a[3];
        int l22 = 0, l11 = 0;
        l22 = a[3] * 5;
        l11 = a[4] * 11;
        if(a[2] > 4){
            boxNum += a[2] / 4;
            a[2] -= a[2] / 4 * 4;
        }
    }
    return 0;
}

