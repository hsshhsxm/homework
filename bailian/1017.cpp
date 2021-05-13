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
        int u[4] = {0, 5, 3, 1};//装3*3后2x的2数目
        boxNum = a[5] + a[4] + a[3] + (a[2] + 3) / 4;
        int l22 = 0, l11 = 0;
        l22 = a[3] * 5 + u[a[2] % 4];
        if(a[1] > l22)
            boxNum += (a[1] - l22 + 8) / 9;
        l11 = boxNum * 36 - a[5]*36 - a[4]*25 - a[3]*16 - a[2]*9 - a[1]*4;
        if(a[0] > l11)
            boxNum += (a[0] - l11 + 35) / 36;
        cout << boxNum << endl;
    }
    return 0;
}

