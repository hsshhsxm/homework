#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    int K;
    int N;
    int h[100];
    int road[100];
    cin >> K;
    while(K--){
        memset(h, 0, sizeof(h));
        memset(road, 0, sizeof(road));
        cin >> N;
        for(int i = 0; i < N; ++i)
            cin >> h[i];
        int res = 0;
        for(int i = 0; i < N; ++i){
            road[i] = 1;
            for(int j = 0; j < i; ++j)
                if(h[i] < h[j])
                    road[i] = max(road[i], road[j] + 1);
            res = max(res, road[i]);
        }
        for(int i = N - 1; i >= 0; --i){
            road[i] = 1;
            for(int j = N - 1; j > i; --j)
                if(h[i] < h[j])
                    road[i] = max(road[i], road[j] + 1);
            res = max(res,road[i]);
        }
        cout << res << endl;
    }
    return 0;
}

