#include <iostream>
#include <algorithm>
using namespace std;

int L,N,M;
int d[50005];

bool judge(int dis){//是否存在m <= M，使得移除m个石头后，最长的最短距离是dis
    int m = 0;
    int begin = 0;
    for(int i = 1; i < N + 2; ++i){ 
        if(d[i] - d[begin] < dis){
            if(++m > M)
                return false;
        }
        else
            begin = i;
    }
    return true;
}

int main()
{
    cin >> L >> N >> M;
    d[0] = 0;
    for(int i = 1; i < N+1; ++i)
        cin >> d[i];
    d[N+1] = L;
    sort(d, d+N+1);
    int leftSide, rightSide;
    leftSide = 0;
    rightSide = L;
    int res;
    while(leftSide <= rightSide){
        int mid = leftSide + (rightSide - leftSide) / 2;
        if(judge(mid)){
            res = mid;
            leftSide = mid + 1;
        }
        else 
            rightSide = mid - 1;
    }
    cout << res << endl;
    return 0;
}