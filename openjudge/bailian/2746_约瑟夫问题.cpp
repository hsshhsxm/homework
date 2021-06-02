#include <iostream>
using namespace std;

int main()
{
    int n,m;
    while(true){
        cin >> n >> m;
        if(n == 0 && m == 0)
            break;
        int monkey[300] = {0};
        int i = -1;
        int left = n;
        int count = 0;
        while(left > 1){
            count++;
            i = (i + 1) % n;
            while(monkey[i] == 1)
                i = (i + 1) % n;
            if(count == m){
                monkey[i] = 1;
                left--;
                count = 0;
            }
        }
        for(int k = 0; k < n; ++k)
            if(monkey[k] == 0)
                cout << k + 1 << endl;
    }
    return 0;
}

