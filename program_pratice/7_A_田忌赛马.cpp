#include <iostream>
#include <algorithm>
using namespace std;

int n;
int tian[1000];
int king[1000];
int main()
{
    cin >> n;
    while(n != 0){
        for(int i = 0; i < n; ++i)
            cin >> tian[i];
        for(int i = 0; i < n; ++i)
            cin >> king[i];
        sort(tian, tian + n, greater<int>());
        sort(king, king + n, greater<int>());
        int tianFast = 0, tianSlow = n - 1, kingFast = 0, kingSlow = n - 1;
        int money = 0;
        for(int i = 0; i < n; ++i){
            if(tian[tianFast] > king[kingFast]){
                money += 200;
                tianFast++;
                kingFast++;
            }
            else if(tian[tianSlow] > king[kingSlow]){
                money += 200;
                tianSlow--;
                kingSlow--;
            }
            else if(tian[tianSlow] == king[kingFast]){
                tianSlow--;
                kingFast++;
            }
            else{
                money -= 200;
                tianSlow--;
                kingFast++;
            }
        }
        cout << money << endl;
        cin >> n;
    }
    return 0;
}