#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
using namespace std;
int main()
{
    freopen("in.txt","w",stdout);
    srand((unsigned)time(NULL));
    cout << 1000 << endl;
    for(int i = 0; i < 1000; i++)
    {
    cout << (rand()%10001)<<" ";       
    cout << endl;
    for (int i = 0; i < 5; i++)
            cout << ((rand() % 10000)+1) << " "; 
    cout << endl;
    }

}