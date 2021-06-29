#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    int n,m;
    int f[12885], w[3405], d[3405];
    memset(f, 0, sizeof(f));
    memset(w, 0, sizeof(w));
    memset(d, 0, sizeof(d));
    cin >> n >> m;
    for(int i = 0; i < n; ++i)
        cin >> w[i] >> d[i];
    for(int i = 0; i < n; ++i)
        for(int j = m; j >= w[i]; --j)
            f[j] = max(f[j], d[i] + f[j - w[i]]);
    cout << f[m] << endl;
    return 0;
}