#include <iostream>
using namespace std;

int main()
{
    int L,M;
    cin >> L >> M;
    int a[100][2];
    for(int i = 0; i < M; ++i)
        cin >> a[i][0] >> a[i][1];
    int road[10001] = {0};
    for(int i = 0; i < M; ++i){
        for(int j = a[i][0]; j <= a[i][1]; ++j)
            road[j] = 1;
    }
    int count = 0;
    for(int i = 0; i <= L; ++i)
        if(road[i] == 0)
            ++count;
    cout << count << endl;
    return 0;
}

