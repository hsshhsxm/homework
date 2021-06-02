#include <iostream>
#include <cstring>
using namespace std;

int N;
int a[30][50] = {0};
// TODO WA
int ways(int i, int j, int n){
    if(n == 0)
        return 1;
    a[i][j] = 1;
    int num = 0;
    if(! a[i][j-1])
        num += ways(i,j-1,n-1);
    if(! a[i][j+1])
        num += ways(i,j+1,n-1);
    if(! a[i+1][j])
        num += ways(i+1,j,n-1);
    return num;
}

int main()
{
    cin >> N;
    memset(a,0,sizeof(a));
    cout << ways(0,25,N) << endl;
    return 0;
}